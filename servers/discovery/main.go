/**
 * @filename main.go
 * @description Discovery server entry point
 *
 * @date 2023-10-6
 * @version 0.0.1
 */

// TODO: Add monitoring systems to monitor the peers and remove the ones that are offline
// TODO: Add monitoring systems to monitor the peers and remove the ones that display malicious behavior
// TODO: Refactor this to use JSON-RPC instead of HTTP

package main

import (
	"flag"								/** Command line arguments parser */
	"fmt"								/** Formatting library */
	"net"								/** Network library */
	"net/http"							/** HTTP server */
	"github.com/rs/zerolog"				/** Logging library */
	"github.com/rs/zerolog/log"			/** Logging library */
	_ "github.com/mattn/go-sqlite3"		/** SQLite3 driver */
	"github.com/oschwald/geoip2-golang"	/** GeoIP database */
)

var (
	/** Command line arguments */
	port = flag.Int("port", 8080, "Discovery server port")				/** Discovery server port */
	host = flag.String("host", "localhost", "Discovery server host")	/** Discovery server host */
	db = flag.String("db", "peers.db", "Discovery server database")		/** Discovery server database */
)

const (
	MaxPeers = 100							/** Maximum number of peers to return in a single request */
	GeoIPDatabase = "GeoIP2-City.mmdb"		/** Path to the GeoIP database */
	DistanceWeight = 0.6					/** Weight of the distance in the peer sorting algorithm */
	LastSeenWeight = 0.4					/** Weight of the last seen time in the peer sorting algorithm */
	PeerSweepInterval = 5 * time.Minute		/** Interval at which the peers are swept to remove the offline ones */
)

struct Peer {
	Hostname string			/** Hostname of the peer */
	IP string				/** IP address of the peer */
	Port int				/** Port on which the peer is listening */
	PubKey string			/** EC secp256k1 Public key of the peer */
	Signature string 		/** Signature of the peer's UUID */
	RegisteredAt time.Time  /** Time at which the peer registered itself */
	LastSeenAt time.Time    /** Time at which the peer was last seen */
	IsOnline bool			/** Whether the peer is online or not */
}

/** List of peers */
type PeerList struct {
	Peers []Peer
}

/** Coordinates */
type Coordinates struct {	/** Used to calculate the distance between two peers */
	Latitude float64
	Longitude float64
}

/**
 * @description Creates the database and the table if they don't exist
 */
func createDatabase() bool {
	db, err := sql.Open("sqlite3", *db)
	if err != nil return false 
	defer db.Close()

	_, err = db.Exec(`CREATE TABLE IF NOT EXISTS peers (
		hostname varchar(255),
		ip varchar(15) NOT NULL,
		port int NOT NULL,
		pubkey varchar(88) PRIMARY KEY NOT NULL,
		signature varchar(88) NOT NULL,
		registered_at datetime NOT NULL,
		last_seen_at datetime NOT NULL,
		is_online boolean NOT NULL DEFAULT 1
	)`)
	if err != nil return false 

	_, err = db.Exec(`CREATE INDEX IF NOT EXISTS idx_peers_uuid ON peers (uuid)`)
	if err != nil return false

	return true
}

/**
 * @description Returns the IP address of the client that made the request
 * @param r The HTTP request
 * @return The IP address of the client
 */
func getIP(r *http.Request) string {
	ip := r.Header.Get("X-Forwarded-For")
	if ip == "" {
		ip, _, _ = net.SplitHostPort(r.RemoteAddr)
	}
	return ip
}

/**
 * @description Returns the peer with the given IP address
 * @param ip The IP address of the peer
 * @return The peer with the given IP address
 */
func getPeerByIP(ip string) Peer {
	/** Open the database */
	db, err := sql.Open("sqlite3", *db)
	if err != nil { 
		log.Fatal().Err(err).Msg("Failed to open database") 
	}
	defer db.Close()

	/** Get the peer */
	peer := Peer{}
	err = db.QueryRow("SELECT uuid, ip, port, registered_at, last_seen_at FROM peers WHERE ip = ?", ip)
					 .Scan(&peer.UUID, &peer.IP, &peer.Port, &peer.RegisteredAt, &peer.LastSeenAt)

	if err != nil {
		log.Fatal().Err(err).Msg("Failed to get peer by IP")
	}

	return peer
}

/**
 * @description Returns a list of all the peers
 * @return A list of all the peers
 */
func getPeers() PeerList {
	/** Open the database */
	db, err := sql.Open("sqlite3", *db)
	if err != nil { 
		log.Fatal().Err(err).Msg("Failed to open database") 
	}
	defer db.Close()

	/** Get the peers */
	rows, err := db.Query("SELECT uuid, ip, port, registered_at, last_seen_at FROM peers")
	if err != nil {
		log.Fatal().Err(err).Msg("Failed to get peers")
	}
	defer rows.Close()

	/** Build the list of peers */
	peers := PeerList{}
	for rows.Next() {
		peer := Peer{}
		err := rows.Scan(&peer.UUID, &peer.IP, &peer.Port, &peer.RegisteredAt, &peer.LastSeenAt)
		if err != nil {
			log.Fatal().Err(err).Msg("Failed to scan peer")
		}
		peers = append(peers, peer)
	}

	return peers
}


/**
 * @description Returns the distance between two coordinates
 * @param coordinatesA The first coordinates
 * @param coordinatesB The second coordinates
 * @return The distance between the two coordinates
 */
func getDistanceFromCoordinates(Coordinates coordinatesA, Coordinates coordinatesB) float64 {
	/** Convert coordinates to radians */
	latA := coordinatesA.Latitude  * math.Pi / 180.0
	lonA := coordinatesA.Longitude * math.Pi / 180.0
	latB := coordinatesB.Latitude  * math.Pi / 180.0
	lonB := coordinatesB.Longitude * math.Pi / 180.0

	/** Calculate distance */
	theta := lonA - lonB
	dist := math.Sin(latA) * math.Sin(latB) + math.Cos(latA) * math.Cos(latB) * math.Cos(theta)
	dist = math.Acos(dist)
	dist = dist * 180.0 / math.Pi
	dist = dist * 60 * 1.1515

	/** Convert to kilometers */
	dist = dist * 1.609344

	return dist
}

/**
 * @description Returns the distance between two peers
 * 
 * This is needed to determine which peers are the closest to the requesting peer
 * so that we can return the closest peers first.
 *
 * @param peerA The first peer
 * @param peerB The second peer
 * @return The distance between the two peers
 */
func getDistanceFromPeers(Peer peerA, Peer peerB) float64 {
	db, err := geoip2.Open(GeoIPDatabase)
	if err != nil {
		log.Fatal().Err(err).Msg("Failed to open GeoIP database")
	}
	defer db.Close()

	/** Get the IP addresses of the peers */
	ipA := net.ParseIP(peerA.IP)
	ipB := net.ParseIP(peerB.IP)

	/** Get the GeoIP records for the peers */
	recordA, err := db.City(ipA)
	if err != nil {
		log.Fatal().Err(err).Msg("Failed to get GeoIP record for peer A")
	}

	recordB, err := db.City(ipB)
	if err != nil {
		log.Fatal().Err(err).Msg("Failed to get GeoIP record for peer B")
	}

	/** Get the coordinates and calculate the distance */
	coordinatesA := Coordinates{Latitude: recordA.Location.Latitude, Longitude: recordA.Location.Longitude}
	coordinatesB := Coordinates{Latitude: recordB.Location.Latitude, Longitude: recordB.Location.Longitude}
	return getDistanceFromCoordinates(coordinatesA, coordinatesB)
}

/**
 * @description Returns the list of the most relevant peers for the requesting peer
 * @param peer The requesting peer
 * @return The list of the most relevant peers for the requesting peer
 */
func buildPeerList() PeerList {
	/** Get the list of all peers */
	peers := getPeers()
	distances := make(map[string]int)

	/** Get the requesting peer */
	requestingPeer := getPeerByIP(getIP(r))

	/** Get the distance between the requesting peer and all other peers except itself */
	for _, peer := range peers {
		if peer.UUID == requestingPeer.UUID continue
		distances[peer.UUID] = getDistanceFromPeers(requestingPeer, peer)
	}

	/** Sort the peers by distance and last seen time according to the weights */
	sort.Slice(peers, func(i, j int) bool {
		return distances[peers[i].UUID] * DistanceWeight + peers[i].LastSeenAt * LastSeenWeight <
			   distances[peers[j].UUID] * DistanceWeight + peers[j].LastSeenAt * LastSeenWeight
	})

	/** Return the list of the most relevant peers */
	return peers[:MaxPeers]
}


/** SERVER HANDLERS */
/**
 * @description Handles the request to get the peers list
 * @param w The HTTP response writer
 * @param r The HTTP request
 */
func peersHandler(w http.ResponseWriter, r *http.Request) {
	log.Info().Msg("Handling peers request from " + getIP(r))

	/** Get the list of the most relevant peers */
	peers := buildPeerList()

	/** Return the list of the most relevant peers */
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(peers)

	log.Info().Msg("Handled peers request from " + getIP(r) + " | " + len(peers) + " peers returned")
}

/**
 * @description Handles the request to get a peer
 * @param w The HTTP response writer
 * @param r The HTTP request
 */
func peerHandler(w http.ResponseWriter, r *http.Request) {
	log.Info().Msg("Handling peer request from " + getIP(r))

	/** Get the Public Key of the peer */
	pubKey := r.URL.Path[len("/peers/"):]
	if pubKey == "" {
		log.Error().Msg("Failed to get peer by public key")
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	/** Get the peer */
	peer := getPeerByPubKey(pubKey)

	/** Return the peer */
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(peer)

	log.Info().Msg("Handled peer request from " + getIP(r) + " | " + peer.PubKey + " returned")
}

/**
 * @description Checks if a peer is online by sending an HTTP request
 * @param pubKey The public key of the peer
 * @return Whether the peer is online or not
 */
func pingPeer(pubKey string) bool {
	/** Get the peer */
	peer := getPeerByPubKey(pubKey)

	/** Send the request */
	resp, err := http.Get("http://" + peer.IP + ":" + peer.Port + "/ping")
	if err != nil return false

	/** Check the response */
	if resp.StatusCode != http.StatusOK return false

	return true
}

/**
 * @description Cleansup the database.
 * 
 * This function is called periodically to mark the peers that are offline and 
 * remove the ones that have been flagged as malicious.
 * 
 * TODO: Add monitoring functions for malicious behavior
 */
func peerSweep() {
	/** Open the database */
	db, err := sql.Open("sqlite3", *db)
	if err != nil { 
		log.Fatal().Err(err).Msg("Failed to open database") 
	}
	defer db.Close()

	/** Get the peers */
	rows, err := db.Query("SELECT uuid, ip, port, registered_at, last_seen_at FROM peers")
	if err != nil {
		log.Fatal().Err(err).Msg("Failed to get peers")
	}
	defer rows.Close()

	/** Check if the peers are online */
	for rows.Next() {
		peer := Peer{}
		err := rows.Scan(&peer.UUID, &peer.IP, &peer.Port, &peer.RegisteredAt, &peer.LastSeenAt)
		if err != nil {
			log.Fatal().Err(err).Msg("Failed to scan peer")
		}

		/** Check if the peer is online */
		if !pingPeer(peer.UUID) {
			/** Mark the peer as offline */
			_, err := db.Exec("UPDATE peers SET is_online = 0 WHERE uuid = ?", peer.UUID)
			if err != nil {
				log.Fatal().Err(err).Msg("Failed to mark peer as offline")
			}
		}
	}
}


/**
 * @description Command line interface
 */
func CLI() {
	for {
		time := time.Now()
		fmt.Printf("[%d:%d:%d] > ", time.Hour(), time.Minute(), time.Second())
		var command string
		fmt.Scanln(&command)

		switch command {
		case "peers":
			fmt.Println("Getting peers...")
			peers := getPeers()
			fmt.Println(peers)
		case "exit":
			fmt.Println("Exiting...")
			os.Exit(0)
		default:
			fmt.Println("Unknown command")
		}
	}
}


/**
 * @description Entry point for the discovery server
 *
 * Usage: ./discovery -port=8080 -host=localhost -db=peers.db
 *
 * @return The exit code
 */
func main() {
	flag.Parse()
	zerolog.SetGlobalLevel(zerolog.DebugLevel)
	log.Logger = log.Output(zerolog.ConsoleWriter{Out: log.Output(zerolog.ConsoleWriter{Out: os.Stderr})})
	
	log.Info().Msg("Starting Skynet discovery server")
	log.Info().Msgf("Listening on %s:%d", *host, *port)
	log.Info().Msgf("Using database %s", *db)

	/** Create the database if it doesn't exist */
	if (!createDatabase()) {
		log.Fatal().Msg("Failed to create database")
	}

	/** Register the handlers */
	http.HandleFunc("/peers", peersHandler)
	http.HandleFunc("/peers/", peerHandler)
	http.HandleFunc("/peers/register", registerHandler)
	http.HandleFunc("/peers/unregister", unregisterHandler)

	/** Start the server on a different go routine */
	go func() {
		log.Fatal().Err(http.ListenAndServe(
			fmt.Sprintf("%s:%d", *host, *port), nil)
		).Msg("Failed to start server")
	}()

	/** Start the peer sweep routine */
	go func() {
		for {
			peerSweep()
			time.Sleep(PeerSweepInterval)
		}
	}()

	/** Start the command line interface */
	CLI()

	log.Info().Msg("Stopping Skynet discovery server")
	return 0
}
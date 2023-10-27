# Node Config

Skynet Nodes use configuration files to define their behaviour. The configuration file is a JSON file that contains the following fields:

```json
{
      "node": {
            "type": "full",         
            "port": 8080,
            "host": "194.168.1.109",
            "miner": {
                  "type": "cpu",
                  "threads": "max"
            }
      },
      "network": {
            "seed-servers": [
                  "skynet1.seed.net:8080",
                  "skynet2.seed.net:8080",
                  "skynet3.seed.net:8080"
            ],
            "max-peers": 200
      },
      "database": {
            "type": "sqlite",
            "path": "skynet.db"
      },
      "wallet": {
            "type": "file",
            "path": "wallet.dat"
      },
      "chain": {
            "name": "skynet-mainnet",
            "type": "pow",
            "local": false,
      }
}
```

## Node

The `node` field defines the behaviour of the node. It contains the following fields:

- `type` - The type of node. Can be `full`, `light` or `miner` (check [node types](./running_a_node.md#node-types) for more information).
- `port` - The port that the node will listen on.
- `host` - The host that the node will listen on.
- `miner` - The miner configuration (only required if the node type is `miner` or `full`).
      - `type` - The type of miner. Can be `cpu` or `cuda`.
      - `threads` - The number of threads that the miner will use. Can be `max` or a number.

## Network

The `network` field defines the network configuration. It contains the following fields:

- `seed-servers` - A list of seed servers that the node will connect to (check the [seed server list](seed_servers.md#server-list) for more information).
- `max-peers` - The maximum number of peers that the node will connect to.

## Database

The `database` field defines the database configuration. It contains the following fields:

- `type` - The type of database. Only `sqlite` is supported at the moment.
- `path` - The path to the database file.

## Wallet

The `wallet` field defines the wallet configuration. It contains the following fields:

- `type` - The type of wallet. Only `file` is supported at the moment.
- `path` - The path to the wallet file.

## Chain

The `chain` field defines the blockchain configuration. Nodes can only connect to nodes that are running the same chain. The mainnet chain is `skynet-mainnet`, but you can also run your own chain by setting the `local` field to `true` and defining a custom `name` for your chain. It contains the following fields:

- `name` - The name of the chain.
- `type` - The type of chain. Can be `pow` or `pos` (only pow supported at the moment).
- `local` - Whether or not the chain is local.
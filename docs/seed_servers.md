# Skynet Seed Servers

**Skynet Seed Servers** are special hardcoded servers that are used to bootstrap the peer-to-peer network. They serve as the initial connection point for new nodes, and they are responsible for connecting nodes to each other and monitoring the network.

## Server List

| Name | Address | Port |
|------|---------|------|
| Seed Server 1 | skynet1.seed.net | 8080 |
| Seed Server 2 | skynet2.seed.net | 8080 |
| Seed Server 3 | skynet3.seed.net | 8080 |

## Peer Discovery Protocol

Seed servers keep a list of all the existing nodes in the network. When a new node connects to a seed server, the seed server registers the node and broadcasts it to the other seed servers.

After this, the node prompts the seed server to send it a list of all the other **n** nodes it should connect to. Nodes are selected from the list of nodes based on their relevance in relation to the requesting node (as well as other factors):

- **Relevance** - Nodes that are more relevant to the requesting node are prioritized over nodes that are less relevant. For example, nodes that are geographically closer to the requesting node are prioritized over nodes that are geographically further away.
- **Availability** - Nodes that are more available are prioritized over nodes that are less available. For example, nodes that are online are prioritized over nodes that are offline.
- **Load** - Nodes that are less loaded are prioritized over nodes that are more loaded. For example, nodes that have less connections are prioritized over nodes that have more connections.

Once the seed server has selected **n** nodes, it sends the list of nodes to the requesting node. The requesting node then connects to the nodes in the list.

> **n** = The number of nodes that the requesting node should connect to.

## Network Monitoring

The seed servers are also responsible for monitoring the network and ensuring that the network is healthy. They do this by periodically analyzing the network and checking if there are any nodes that are not behaving correctly. If a node is found to be misbehaving, the seed servers can timeout the node, or even ban it from the network.

A ping sweep is also performed periodically to check if the nodes are still online. If a node is found to be offline, the seed servers can flag it as offline, and remove it from the list of nodes until it comes back online.

## Running a Seed Server

In order to run a seed server, you must first submit a request to the [Skynet Discord Server](https://discord.gg/2Yb2V2r) with a detailed report following the template below:

```text
Name: <your name>
Email: <your email>
Server Address: <your server address>
Server Port: <your server port>
Server Location: <your server location>
Public Key: <your public key>

Server Specs:
<server specs>

Additional Information:
<additional information>

Digital Signature: <your digital signature in base64>
```

Once your request is approved, the skynet team will contact you with further instructions on how to setup your server.

### How can I maximize my chances of getting approved?

- **Server Location** - If your server location enables the network to setup a seed server on a new region.
- **Server Specs** - If your server specs are good enough to handle the load of a seed server.
- **Additional Information** - If you provide additional information that can help the network (e.g. you are a blockchain enthusiast, you have experience with blockchain, etc...).
- **Contributions** - If you have contributed to the project in the past.
- **Donations** - If you have donated to the project in the past.
- **Community** - If you are an active member of the community.
- **Network Contribution** - If you have contributed to the network in the past (e.g. you have run a node in the past, you have mined blocks in the past, etc...).
- **Availability** - If you are available to maintain the server and keep it online for as long as possible, with as little downtime as possible.

---

**Note:** The Skynet team reserves the right to deny any request without further explanation; as well as the right to remove any seed server from the list at any time uppon reaching a consensus with the other seed server operators and community members.

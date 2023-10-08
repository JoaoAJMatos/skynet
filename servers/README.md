# Skynet Servers

This directory contains the implementations for the servers Skynet needs in order to work and to kickstart the network.

## Bootstrapping and Peer Discovery

The bootstrapping and peer discovery process is done by the [discovery server](discovery/README.md). 

The discovery servers are the only servers that are ran by the Skynet team. They are ran on a set of dedicated servers and are the only servers that are allowed to be used for bootstrapping and peer discovery.

The list of authorized servers is maintained in the [discovery server list]() GitHub Gist.
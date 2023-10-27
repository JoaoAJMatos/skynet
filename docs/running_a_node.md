# Running a Node

In order to run a Skynet node you must first download the latest installer from the [releases]() page.

## Skynet Core CLI

The default environment for Skynet Core is the command line interface. To start a node, simply run the following command:

```bash
skynet-core --config <path_to_config_file>
```

Checkout the [config](./config.md) page for more information on how to configure your node.

## Skynet Core GUI

Skynet Core also comes with a graphical user interface. To start a node with the GUI, simply run:

```bash
skynet-core-gui --config <path_to_config_file>
```

---

> **Note**: The config file does not need to exist. If the path specified does not contain a skynet node configuration file, the file is created with the default configs.

## Node types

- **Full Node** - A full node is a node that stores the entire blockchain history. **It is capable of validating transactions and blocks, and it can also mine new blocks**.
- **Light Node** - A light node is a node that does not store the entire blockchain history. It is not capable of validating transactions and blocks, and it cannot mine new blocks. **It can only be used to send and receive transactions**.
- **Miner Node** - A miner node is a node that is capable of mining new blocks. It is not capable of validating transactions and blocks, and it does not store the entire blockchain history. **It can only be used to mine new blocks**.
# Skynet Core

**Skynet**, an educational Blockchain implementation in C++.

## Motivation

When I was 17, crypto was booming. I was fascinated by the idea of a decentralized currency, and I wanted to learn more about it. So, as any normal 17 year old would do, I decided to build my own cryptocurrency from scratch in C++.

As you can imagine, the resulting code was the pure definition of spaghetti. I already had some experience with C++, but I couldn't quite grasp some of the concepts surrouding blockchain. I often found myself digging through other people's code, trying to understand how they implemented certain mechanisms. I scavenged through Bitcoin's codebase, and I even found a few examples of blockchain implementations on GitHub. But they were all too "complex" for me at that point.

When learning how to implement the underlying infrastructure of blockchain, I noticed that most of the examples I found were just like that, with codebases that were too large, interconnected, and difficult to understand.

For that reason, I decided to rewrite my own blockchain from scratch, but this time, with a focus on simplicity and readability. I wanted to create a codebase that was easy to understand, and that could be used as a learning tool for others.

## Features

- **Network layer**
- **Consensus**
- **Wallets**
- **Transactions**
- **Mining**
- **Scripting** (wip)

## Installation

In order to install Skynet Core, you can download one of the pre compiled binaries from the [releases]() page.

Alternatively, you can build the project from source by running one of the following commands:

**Linux/MacOs**:

```bash
git clone https://github.com/JoaoAJMatos/skynet.git
cd skynet
./scripts/build.sh            # Compile libskynet
./scripts/build_core.sh       # Compile skynet-core
```

**Windows**:

```bash
git clone https://github.com/JoaoAJMatos/skynet.git
cd skynet
./scripts/build.bat           # Compile libskynet
./scripts/build_core.bat      # Compile skynet-core
```

## Running

Checkout the [running a node](./running_a_node.md) page for more information on how to run a node.

## Contributing

If you want to contribute to Skynet Core, please read the [contributing](./CONTRIBUTING.md) page.

## License

Skynet Core is licensed under the [MIT License](./LICENSE)
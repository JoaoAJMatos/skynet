/**
 * @file   node.hpp
 * @author JoaoAJMatos
 *
 * @brief This header file contains the logic for a Skynet node. It provides the interface
 *        for the node to interact with the network and the blockchain.
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

/* C++ Includes */
#include <stdexcept>
#include <memory>

/* Skynet Includes */
#include <net/client.hpp>
#include <net/server.hpp>

/* Local Includes */
#include "base_miner.hpp"

namespace skynet
{
      enum NodeType
      {
            FULL_NODE,
            LIGHT_NODE, 
            MINER_NODE
      };

      /** TRANSPORT INTERFACES */
      class NodeServer : public net::Server
      {
      };

      class NodeClient : public net::Client
      {
      };

      /** NODE EXCEPTION */
      class NodeException : public std::runtime_error
      {
      public:
            NodeException(const char *message) : std::runtime_error(message) {}
            NodeException(const std::string &message) : std::runtime_error(message) {}
            virtual ~NodeException() {}

            virtual const char *what() const noexcept override
            {
                  return std::runtime_error::what();
            }

      private:
            std::string message;
      };

      /** NODE CLASS */
      class Node
      {
      public:
            Node(NodeType type);
            ~Node();

            /** Starts the node */
            void Start();
            /** Stops the node */
            void Stop();

            /** Getters */
            [[nodiscard]] NodeType GetType() const { return type; }
            [[nodiscard]] NodeServer *GetServer() const { return server; }
            [[nodiscard]] NodeClient *GetClient() const { return client; }

            /** Setters */
            void SetMiner(std::shared_ptr<Miner> miner) { this->miner = miner; }
      private:
            /** Bootstrap the node */
            void Bootstrap();
            /** Load config */
            void LoadConfig();
            /** Save config */
            void SaveConfig();
            /** Reload config */
            void ReloadConfig();
            /** Fetch peers */
            void FetchPeers();
            /** Connect to peers */
            void ConnectToPeers();
            /** Sync with peers */
            void SyncWithPeers();

            NodeType type;
            NodeServer *server;
            NodeClient *client;

            std::shared_ptr<Miner> miner;
      };
} // namespace skynet

// MIT License
// 
// Copyright (c) 2023 João Matos
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

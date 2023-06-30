/**
 * @file node.hpp
 * @author JoaoAJMatos
 * @brief The p2p network node
 * @date 2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SKYNET_NODE_HPP
#define SKYNET_NODE_HPP

#include <net/client.hpp>
#include <net/server.hpp>
#include <io/threadsafe_logger.hpp>
#include <threading/threadpool.hpp>

namespace skynet
{
      class NodeServer : public net::Server
      {
      public:
      private:
            ThreadPool threadpool_;
      };

      class NodeClient : public net::Client
      {};

      class Node
      {
      public:

      private:
            NodeServer server_;
            NodeClient client_;
      };
}

#endif //!SKYNET_NODE_HPP

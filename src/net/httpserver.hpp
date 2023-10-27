/**
 * @file    httpserver.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file defines the HTTP server that Skynet uses.
 *
 * @date    2023-09-28
 * 
 * @copyright Copyright (c) 2023
 * @license MIT
 */

#ifndef SKYNET_HTTPSERVER_HPP
#define SKYNET_HTTPSERVER_HPP

/** C++ Includes */
#include <map>
#include <string>
#include <functional>

/** Skynet Includes */
#include <net/server.hpp>

namespace net
{
      /** Type Aliases */
      using HTTPHandler = std::function<HTTPResponse(HTTPRequest)>;

      /** Constants */
      constexpr int HTTP_PORT = 8080;

      /**
       * @brief HTTP Request
       */
      struct HTTPRequest
      {
            std::string method;
            std::string path;
            std::string body;
            std::map<std::string, std::string> headers;

            HTTPRequest(std::string method, std::string path, std::string body, std::map<std::string, std::string> headers) : 
                        method(method), path(path), body(body), headers(headers) {}
      };

      /**
       * @brief HTTP Response
       */
      struct HTTPResponse
      {
            int status_code;
            std::string body;
            std::map<std::string, std::string> headers;

            HTTPResponse(int status_code, std::string body, std::map<std::string, std::string> headers) : 
                        status_code(status_code), body(body), headers(headers) {}
      };

      /**
       * @brief HTTP Server
       * 
       * @details This class implements the HTTP server used as the transport layer
       *          for JSON-RPC requests.
       * 
       * @see net::Server
       */
      class HTTPServer : public Server
      {
      public:
            HTTPServer(int port, int backlog = DEFAULT_BACKLOG) : Server(port, Protocol::TCP, backlog) {}
            ~HTTPServer() = default;

            /** Registers a handler for a given path */
            void RegisterHandler(std::string path, HTTPHandler handler);

      private:
            /** Function Overrides */
            void Launch() override;
            bool Accept() override;
            void Shutdown() override;

            /** Handles a request */
            void HandleRequest();

            /** HTTP handlers map */
            std::map<std::string, HTTPHandler> handlers;
      };

} // namespace net

#endif // SKYNET_HTTPSERVER_HPP
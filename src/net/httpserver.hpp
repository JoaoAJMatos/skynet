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
#include <stdexcept>

/** Skynet Includes */
#include <net/server.hpp>

namespace net
{
      /** Constants */
      constexpr int HTTP_PORT = 8080;

      enum class HTTPMethod
      {
            GET,
            POST,
            PUT,
            DELETE,
            PATCH,
            HEAD,
            OPTIONS,
            CONNECT,
            TRACE
      };

      enum class HTTPStatusCode
      {
            OK = 200,
            CREATED = 201,
            ACCEPTED = 202,
            NO_CONTENT = 204,
            MOVED_PERMANENTLY = 301,
            FOUND = 302,
            NOT_MODIFIED = 304,
            BAD_REQUEST = 400,
            UNAUTHORIZED = 401,
            FORBIDDEN = 403,
            NOT_FOUND = 404,
            METHOD_NOT_ALLOWED = 405,
            INTERNAL_SERVER_ERROR = 500,
            NOT_IMPLEMENTED = 501,
            BAD_GATEWAY = 502,
            SERVICE_UNAVAILABLE = 503
      };

      /**
       * @brief Returns the string representation of a HTTP method.
       * 
       * @param method The HTTP method.
       * @return std::string The string representation of the HTTP method.
       */
      std::string HTTPMethodToString(HTTPMethod method);

      /**
       * @brief Returns the HTTP method from a string.
       * 
       * @param method The string representation of the HTTP method.
       * @return HTTPMethod The HTTP method.
       */
      HTTPMethod StringToHTTPMethod(std::string method);

      /**
       * @brief Returns the string representation of a HTTP status code.
       * 
       * @param status_code The HTTP status code.
       * @return std::string The string representation of the HTTP status code.
       */
      std::string HTTPStatusCodeMessage(HTTPStatusCode status_code);

      /**
       * @brief HTTP Exception
       */
      class HTTPException : public std::runtime_error
      {
      public:
            HTTPException(HTTPStatusCode status_code, std::string message) : 
                  std::runtime_error(message), status_code(status_code) {}

            HTTPStatusCode GetStatusCode() const { return this->status_code; }
      
      private:
            HTTPStatusCode status_code;
      };

      /**
       * @brief HTTP Request
       */
      class HTTPRequest 
      {
      public:
            HTTPRequest() = default;
            ~HTTPRequest() = default;

            HTTPRequest(HTTPMethod method, std::string path, std::string body, std::map<std::string, std::string> headers) : 
                  method(method), path(path), body(body), headers(headers) {}

            HTTPRequest(const HTTPRequest& other) : 
                  method(other.method), path(other.path), body(other.body), headers(other.headers) {}

            /** Converts the HTTP Request to a string */
            std::string ToString() const;

            /** Getters */
            HTTPMethod GetMethod() const { return this->method; }
            std::string GetPath() const { return this->path; }
            std::string GetBody() const { return this->body; }
            std::map<std::string, std::string> GetHeaders() const { return this->headers; }

      private:
            HTTPMethod method;
            std::string path;
            std::string body;
            std::map<std::string, std::string> headers;
      };

      /**
       * @brief HTTP Response
       */
      class HTTPResponse
      {
      public:
            HTTPResponse()  = default;
            ~HTTPResponse() = default;

            HTTPResponse(HTTPStatusCode status_code, std::string body, std::map<std::string, std::string> headers) : 
                  status_code(status_code), body(body), headers(headers) {}
            
            HTTPResponse(const HTTPResponse& other) :
                  status_code(other.status_code), body(other.body), headers(other.headers) {}

            /** Converts the HTTP Response to a string */
            std::string ToString() const;

            /** Getters */
            HTTPStatusCode GetStatusCode() const { return static_cast<HTTPStatusCode>(this->status_code); }
            std::string GetBody() const { return this->body; }
            std::map<std::string, std::string> GetHeaders() const { return this->headers; }

      private:
            HTTPStatusCode status_code;
            std::string body;
            std::map<std::string, std::string> headers;
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
            void RegisterHandler(std::string path, std::function<HTTPResponse(HTTPRequest)> handler);

      private:
            /** Function Overrides */
            void Launch() override;       /** Server bootsrap procedure */
            void Accept() override;       /** Accepts a new connection */
            void Shutdown() override;     /** Server shutdown procedure */

            /** Handles a request */
            void HandleRequest(std::string data);

            /** HTTP handlers map */
            std::map<std::string, std::function<HTTPResponse(HTTPRequest)>> handlers;
      };

} // namespace net

#endif // SKYNET_HTTPSERVER_HPP

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
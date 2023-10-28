//
// Created by João Matos on 01/02/2023.
//

/** C++ Includes */
#if not defined(_WIN32) && not defined(_WIN64)
#include <arpa/inet.h>  // for inet_ntoa()
#endif // not defined(_WIN32) && not defined(_WIN64)

/** Local Includes */
#include "httpserver.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////

/** Helper Functions */
/**
 * @brief Splits a string into a vector of strings.
 * 
 * @param str The string to split.
 * @param delimiter The delimiter to use.
 * @return std::vector<std::string> The vector of strings.
 */
static std::vector<std::string> split(std::string str, std::string delimiter) {
      std::vector<std::string> result;
      size_t pos = 0;
      std::string token;
      while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            result.push_back(token);
            str.erase(0, pos + delimiter.length());
      }
      result.push_back(str);
      return result;
}

/**
 * @brief Parses a HTTP request.
 * 
 * @param request_string The request string to parse.
 * @return net::HTTPRequest The parsed request.
 */
static net::HTTPRequest parse_http_request(std::string request_string) {
      /** Split the request into lines */
      std::vector<std::string> lines = split(request_string, "\r\n");

      /** Parse the request line */
      std::vector<std::string> request_line = split(lines[0], " ");
      std::string method = request_line[0];
      std::string path = request_line[1];

      /** Parse the headers */
      std::map<std::string, std::string> headers;
      for (int i = 1; i < lines.size(); i++) {
            std::vector<std::string> header = split(lines[i], ": ");
            headers[header[0]] = header[1];
      }

      /** Parse the body */
      std::string body = "";
      if (headers.find("Content-Length") != headers.end()) {
            int content_length = std::stoi(headers["Content-Length"]);
            body = lines[lines.size() - 1].substr(0, content_length);
      }

      /** Return the request */
      return net::HTTPRequest(net::StringToHTTPMethod(method), path, body, headers);
}

//////////////////////////////////////////////////////////////////////////////////////////////

std::string net::HTTPRequest::ToString() const {
      std::string result = "";
      result += net::HTTPMethodToString(this->method) + " " + this->path + " HTTP/1.1\r\n";
      for (auto& header : this->headers) {
            result += header.first + ": " + header.second + "\r\n";
      }
      result += "\r\n";
      result += this->body;
      return result;
}

std::string net::HTTPResponse::ToString() const {
      std::string result = "";
      result += "HTTP/1.1 " + std::to_string((int)this->status_code) + " " + net::HTTPStatusCodeMessage(this->status_code) + "\r\n";
      for (auto& header : this->headers) {
            result += header.first + ": " + header.second + "\r\n";
      }
      result += "\r\n";
      result += this->body;
      return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief Converts a HTTP method to a string.
 * 
 * @param method The HTTP method.
 * @return std::string The string representation of the HTTP method.
 */
std::string net::HTTPMethodToString(HTTPMethod method) {
      switch (method)
      {
      case HTTPMethod::GET: return "GET";
      case HTTPMethod::POST: return "POST";
      case HTTPMethod::PUT: return "PUT";
      case HTTPMethod::DELETE: return "DELETE";
      case HTTPMethod::HEAD: return "HEAD";
      case HTTPMethod::OPTIONS: return "OPTIONS";
      case HTTPMethod::CONNECT: return "CONNECT";
      case HTTPMethod::TRACE: return "TRACE";
      } // No default case to force compiler warning on missing cases

      return "";
}

/**
 * @brief Converts a string to a HTTP method.
 * 
 * @param method The string representation of the HTTP method.
 * @return HTTPMethod The HTTP method.
 * @throws std::runtime_error If the method is invalid.
 */
net::HTTPMethod net::StringToHTTPMethod(std::string method) {
      if (method == "GET") return HTTPMethod::GET;
      if (method == "POST") return HTTPMethod::POST;
      if (method == "PUT") return HTTPMethod::PUT;
      if (method == "DELETE") return HTTPMethod::DELETE;
      if (method == "HEAD") return HTTPMethod::HEAD;
      if (method == "OPTIONS") return HTTPMethod::OPTIONS;
      if (method == "CONNECT") return HTTPMethod::CONNECT;
      if (method == "TRACE") return HTTPMethod::TRACE;
      else throw std::runtime_error("Invalid HTTP method");
}

/**
 * @brief Returns the message associated with a HTTP status code.
 * 
 * @param status_code The HTTP status code.
 * @return std::string The message associated with the HTTP status code.
 */
std::string net::HTTPStatusCodeMessage(HTTPStatusCode status_code) {
      switch (status_code)
      {
      case HTTPStatusCode::OK : return "OK";
      case HTTPStatusCode::CREATED : return "Created";
      case HTTPStatusCode::ACCEPTED : return "Accepted";
      case HTTPStatusCode::NO_CONTENT : return "No Content";
      case HTTPStatusCode::MOVED_PERMANENTLY : return "Moved Permanently";
      case HTTPStatusCode::FOUND : return "Found";
      case HTTPStatusCode::NOT_MODIFIED : return "Not Modified";
      case HTTPStatusCode::BAD_REQUEST : return "Bad Request";
      case HTTPStatusCode::UNAUTHORIZED : return "Unauthorized";
      case HTTPStatusCode::FORBIDDEN : return "Forbidden";
      case HTTPStatusCode::NOT_FOUND : return "Not Found";
      case HTTPStatusCode::METHOD_NOT_ALLOWED : return "Method Not Allowed";
      case HTTPStatusCode::INTERNAL_SERVER_ERROR : return "Internal Server Error";
      case HTTPStatusCode::NOT_IMPLEMENTED : return "Not Implemented";
      case HTTPStatusCode::BAD_GATEWAY : return "Bad Gateway";
      case HTTPStatusCode::SERVICE_UNAVAILABLE : return "Service Unavailable";
      } // No default case to force compiler warning on missing cases

      return "";
}

/**
 * @brief Registers a handler for the given path.
 * 
 * @param path The path to register the handler for.
 * @param handler The handler to register.
 */
void net::HTTPServer::RegisterHandler(std::string path, std::function<HTTPResponse(HTTPRequest)> handler) {
      this->handlers[path] = handler;
}

/**
 * @brief Launches the HTTP server
 *        
 * @details This method is called by the Run method
 *          in order to bootstrap the server.
 * 
 * @see net::Server::Run
 */
void net::HTTPServer::Launch() {

}

/**
 * @brief Accepts a new connection.
 * 
 * @details This method is called by the Run method 
 *          in order to accept new connections.
 * 
 *          This method will block until a new connection
 *          is accepted.
 * 
 *          Then, it will read the data from the socket
 *          and call the HandleRequest method.
 * 
 * @see net::Server::Run
 */
void net::HTTPServer::Accept() {
      struct sockaddr_in client_address;
      socklen_t client_address_size = sizeof(client_address);

      /** Accept the connection */
      int client_socket = accept(this->GetSocket(), (struct sockaddr *) &client_address, &client_address_size);
      if (client_socket < 0) throw std::runtime_error("Failed to accept connection");
      
      /** Get client information */
      std::string client_ip = inet_ntoa(client_address.sin_addr);
      uint16_t client_port = ntohs(client_address.sin_port);

      /** Read data from the socket */
      std::string data = "";
      char buffer[1024];
      int bytes_read = 0;
      while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0)
            data += std::string(buffer, bytes_read);
      
      /** Handle the request */
      this->HandleRequest(data);
}

/**
 * @brief Handles the given request.
 * 
 * @details This method will parse the request, get the handler
 *          for the given path and call it.
 * 
 *          If no handler is found, it will send a 404 response.
 * 
 * @param request The request to handle.
 */
void net::HTTPServer::HandleRequest(std::string request) {
      HTTPResponse http_response;
      
      try {
            /** Parse the request */
            HTTPRequest http_request = parse_http_request(request);

            /** Get the handler */
            std::function<HTTPResponse(HTTPRequest)> handler = this->handlers[http_request.GetPath()];

            if (handler == nullptr) 
                  http_response = HTTPResponse(HTTPStatusCode::NOT_FOUND, "Not Found", {});
            else 
                  http_response = handler(http_request);

      } catch (HTTPException &e) {
            HTTPStatusCode status_code = e.GetStatusCode();
            http_response = HTTPResponse(status_code, HTTPStatusCodeMessage(status_code), {});
      } catch (std::exception &e) {
            http_response = HTTPResponse(HTTPStatusCode::INTERNAL_SERVER_ERROR, e.what(), {});
      }

      send(this->GetSocket(), http_response.ToString().c_str(), http_response.ToString().length(), 0);
}

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
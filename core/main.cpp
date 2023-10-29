#include <net/httpserver.hpp>

net::HTTPResponse home_handler(net::HTTPRequest request) {
      return net::HTTPResponse(net::HTTPStatusCode::OK, "Hello World!", {});
}

int main(int argc, char** argv) {
      net::HTTPServer server(net::DEFAULT_HTTP_PORT);
      server.RegisterHandler("/", home_handler);
      server.Run();
      return 0;
}
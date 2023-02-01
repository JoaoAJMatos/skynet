#include <iostream>

#include <net/client.hpp>

int main() {
    net::CClient client(net::NET_TCP);

    client.Connect("127.0.0.1", 3000);
    client.Send("Hello World!", 12);
    return 0;
}

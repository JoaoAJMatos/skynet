#ifndef SKYNET_NET_HPP
#define SKYNET_NET_HPP

#include <cstdlib>
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define NET_BUFFER_SIZE 1024

namespace net 
{
      enum class Protocol 
      {
            TCP = 1,
            UDP = 2,
      };
}

#endif // !SKYNET_NET_HPP

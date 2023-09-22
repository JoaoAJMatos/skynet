#ifndef SKYNET_TIME_HPP
#define SKYNET_TIME_HPP

#include <chrono>
#include <ctime>
#include <string>

namespace skynet::time
{
      inline uint64_t timestamp()
      {
            return std::chrono::duration_cast<std::chrono::milliseconds> \
                  (std::chrono::system_clock::now().time_since_epoch()).count();
      }

      std::string timestamp_to_string(uint64_t timestamp)
      {
            std::time_t t = timestamp;
            std::tm* tm = std::localtime(&t);
            char buffer[80];
            std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", tm);
            return std::string(buffer);
      }

      std::string datetime()
      {
            return timestamp_to_string(timestamp());
      }
}

#endif // !SKYNET_TIME_HPP

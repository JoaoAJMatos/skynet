#ifndef SKYNET_TIME_HPP
#define SKYNET_TIME_HPP

/* C++ includes */
#include <chrono>
#include <ctime>
#include <string>

/* Skynet includes */
#include "macros.hpp"

namespace util::time
{
      inline uint64_t timestamp() {
            return TIMESTAMP();
      }

      std::string timestamp_to_string(uint64_t timestamp) {
            std::time_t t = timestamp;
            std::tm* tm = std::localtime(&t);
            char buffer[80];
            std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", tm);
            return std::string(buffer);
      }

      std::string datetime() {
            return timestamp_to_string(timestamp());
      }
}

#endif // !SKYNET_TIME_HPP

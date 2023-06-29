#ifndef SKYNET_MACROS_HPP
#define SKYNET_MACROS_HPP

#include <cassert>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define ASSERT_DEBUG(condition, message) \
      do { \
            if (!(condition)) { \
                  std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                            << " line " << __LINE__ << ": " << message << std::endl; \
                  std::terminate(); \
            } \
      } while (false)

#define UNIMPLEMENTED() ASSERT(false, "Unimplemented")
#define TIMESTAMP() std::chrono::duration_cast<std::chrono::milliseconds> \ (std::chrono::system_clock::now().time_since_epoch()).count()

#endif // SKYNET_MACROS_HPP

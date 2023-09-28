#ifndef SKYNET_MACROS_HPP
#define SKYNET_MACROS_HPP

#include <cassert>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define ASSERT(condition, message) assert((condition) && (message))
#define UNIMPLEMENTED() ASSERT(false, "Unimplemented")
#define TIMESTAMP() std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
#define loop() for (;;)

#ifdef __APPLE__
#define inline __attribute__((always_inline))
#endif // __APPLE__

#endif // SKYNET_MACROS_HPP

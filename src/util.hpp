//
// Created by João Matos on 01/02/2023.
//

#ifndef SKYNET_UTIL_HPP
#define SKYNET_UTIL_HPP

#include <assert.h>

#define loop for (;;)
#define array_size(array) (sizeof(array) / sizeof(array[0]))
#define unimplemented() assert(false, "Unimplemented")
#define timestamp() std::chrono::duration_cast<std::chrono::milliseconds> \
                    (std::chrono::system_clock::now().time_since_epoch()).count()

#endif //SKYNET_UTIL_HPP

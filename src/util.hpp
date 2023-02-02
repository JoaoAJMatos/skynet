//
// Created by João Matos on 01/02/2023.
//

#ifndef SKYNET_UTIL_HPP
#define SKYNET_UTIL_HPP

#include <assert.h>
#include <types.hpp>
#include <iostream>

#define loop for (;;)
#define array_size(array) (sizeof(array) / sizeof(array[0]))
#define unimplemented() assert(false, "Unimplemented")
#define timestamp() std::chrono::duration_cast<std::chrono::milliseconds> \
                    (std::chrono::system_clock::now().time_since_epoch()).count()


static void print_hex(byte *data, size_t size) {
    printf("0x");
    for (size_t i = 0; i < size; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}


#endif //SKYNET_UTIL_HPP

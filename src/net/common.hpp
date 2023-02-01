//
// Created by João Matos on 01/02/2023.
//

#ifndef SKYNET_COMMON_HPP
#define SKYNET_COMMON_HPP

namespace net {
    typedef enum {
        NET_ERROR = -1,
        NET_OK,
    } ErrorCode;

    typedef enum {
        NET_TCP,
        NET_UDP,
    } Protocol;
}


#endif //SKYNET_COMMON_HPP

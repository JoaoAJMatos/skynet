/**
 * @file   ntp.hpp
 * @author Original author: plusangel | Adapted by: JoaoAJMatos
 *
 * @brief This header file contains the implementation of the NTP class.
 *        Nodes can use this class to synchronize their clocks with the
 *        network. The original implementation was made by plusangel and
 *        can be found here: https://github.com/plusangel/NTP-client, I've
 *        addapted it for the SkyNet project.
 *
 * @version 0.1
 * @date 2023-02-01
 * @license Original license: MIT | Adapted license: MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_NTP_HPP
#define SKYNET_NTP_HPP

#include <vector>

#include "types.hpp"
#include "net/client.hpp"

/**
 * @brief NTP Packet structure.
 * 
 *        This struct defines the NTP packet structure: https://tools.ietf.org/html/rfc5905#section-7.3
 *
 *        +-----------+------------+-----------------------+
 *        | Name      | Formula    | Description           |
 *        +-----------+------------+-----------------------+
 *        | leap      | leap       | leap indicator (LI)   |
 *        | version   | version    | version number (VN)   |
 *        | mode      | mode       | mode                  |
 *        | stratum   | stratum    | stratum               |
 *        | poll      | poll       | poll exponent         |
 *        | precision | rho        | precision exponent    |
 *        | rootdelay | delta_r    | root delay            |
 *        | rootdisp  | epsilon_r  | root dispersion       |
 *        | refid     | refid      | reference ID          |
 *        | reftime   | reftime    | reference timestamp   |
 *        | org       | T1         | origin timestamp      |
 *        | rec       | T2         | receive timestamp     |
 *        | xmt       | T3         | transmit timestamp    |
 *        | dst       | T4         | destination timestamp |
 *        | keyid     | keyid      | key ID                |
 *        | dgst      | dgst       | message digest        |
 *        +-----------+------------+-----------------------+
 */
typedef struct {
    byte li_vn_mode;            // li (2 bits), vn (3 bits), mode (3 bits)
    byte stratum;               // stratum level of the local clock (8 bits)
    byte poll;                  // maximum interval between successive messages (8 bits)
    byte precision;             // precision of the local clock (8 bits)
    uint32_t rootDelay;         // total round trip delay time (32 bits)
    uint32_t rootDispersion;    // max error alowed from primary clock source (32 bits)
    uint32_t refId;             // reference clock identifier (32 bits)
    uint32_t refTm_s;           // reference time-stamp seconds (32 bits)
    uint32_t refTm_f;           // reference time-stamp fraction of a second (32 bits)
    uint32_t origTm_s;          // origin time-stamp seconds (32 bits)
    uint32_t origTm_f;          // origin time-stamp fraction of a second (32 bits)
    uint32_t rxTm_s;            // received time-stamp seconds (32 bits)
    uint32_t rxTm_f;            // received time-stamp fraction of a second (32 bits)
    uint32_t txTm_s;            // transmited time-stamp seconds (32 bits)
    uint32_t txTm_f;            // transmited time-stamp fraction of a second (32 bits)
} NTPPacket;


class CNtpClient : public net::CClient {
public:
    CNtpClient()  = default;
    ~CNtpClient() = default;
private:
    uint64_t ntp_timestamp();


    static constexpr unsigned long long NTP_TIMESTAMP_DELTA{2208988800ull};
};


#endif //SKYNET_NTP_HPP

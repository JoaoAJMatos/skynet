#ifndef SKYNET_TIME_HPP

namespace time_utils
{
      std::string GetFormattedTime()
      {
            std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
            std::time_t tt = std::chrono::system_clock::to_time_t(tp);
            std::tm gmt{}; gmtime_r(&tt, &gmt);
            std::chrono::duration<double> fractional_seconds =
                  (tp - std::chrono::system_clock::from_time_t(tt)) + std::chrono::seconds(gmt.tm_sec);

            std::string buffer("year/mo/dy hr:mn:sc.xxxxxx");
            snprintf(&buffer.front(), buffer.size(),
                  "%04d/%02d/%02d %02d:%02d:%09.6f",
                  gmt.tm_year + 1900, gmt.tm_mon + 1,
                  gmt.tm_mday, gmt.tm_hour, gmt.tm_min, fractional_seconds.count());

            return buffer;
      }
}

#endif // !#ifndef SKYNET_TIME_HPP




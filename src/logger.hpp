#ifndef SKYNET_LOGGER_HPP
#define SKYNET_LOGGER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>

#include "time.hpp"

namespace Logging 
{
      enum class LogLevel : uint8_t { TRACE = 0, DEBUG = 1, INFO = 2, WARN = 3, ERROR = 4 };

      class Logger
      {
      public:
            Logger() = default;
            Logger(const Logger&) = delete;
            void operator = (const Logger&) = delete;

            static Logger* GetInstance();
            void SetLogFile(const std::string& filename);

            void Log(LogLevel level, const std::string& message);
            void LogFile(LogLevel level, const std::string& message);

      private:
            std::string m_filename;
            LogLevel m_level;
            std::ofstream m_file;

      protected:
            static Logger* m_instance_;
            std::mutex m_lock_;
      };


      void TRACE(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::TRACE, message);
      }

      void DEBUG(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::DEBUG, message);
      }

      void INFO(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::INFO, message);
      }

      void WARN(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::WARN, message);
      }

      void ERROR(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::ERROR, message);
      }
}

#endif //SKYNET_LOGGER_HPP


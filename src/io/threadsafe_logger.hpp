/**
 * @file threadsafe_logger.hpp
 * @author JoaoAJMatos
 * @brief A thread-safe logger for the stdout and files
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_LOGGER_HPP
#define SKYNET_LOGGER_HPP

/** C++ includes */
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>

/** Local includes */
#include "time.hpp"

namespace Logging 
{
      enum class LogLevel : uint8_t 
      { 
            TRACE = 0, 
            DEBUG = 1, 
            INFO = 2, 
            WARN = 3, 
            ERROR = 4 
      };

      class Logger
      {
      public:
            Logger() = default;
            Logger(const Logger&) = delete;
            void operator = (const Logger&) = delete;

            /** Get the singleton instance */
            static Logger* GetInstance();
            /** Set the file to log the messages to */
            void SetLogFile(const std::string& filename);
            
            /** Log a message to the stdout */
            void Log(LogLevel level, const std::string& message);
            /** Log a message to a file */
            void LogFile(LogLevel level, const std::string& message);

      private:
            std::string m_filename;
            LogLevel m_level;
            std::ofstream m_file;

      protected:
            static Logger* m_instance_;
            std::mutex m_lock_;
      };

      /** These stand out in the code */
      inline void TRACE(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::TRACE, message);
      }

      inline void DEBUG(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::DEBUG, message);
      }

      inline void INFO(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::INFO, message);
      }

      inline void WARN(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::WARN, message);
      }

      inline void ERROR(const std::string& message) {
            Logger::GetInstance()->Log(LogLevel::ERROR, message);
      }
}

#endif //SKYNET_LOGGER_HPP


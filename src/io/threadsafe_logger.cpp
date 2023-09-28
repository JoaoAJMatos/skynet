#include "threadsafe_logger.hpp"

Logging::Logger* Logging::Logger::m_instance_ = nullptr;

Logging::Logger* Logging::Logger::GetInstance() {
      if (m_instance_ == nullptr) {
            m_instance_ = new Logger();
      }
      
      return m_instance_;
}

void Logging::Logger::SetLogFile(const std::string& filename) {
      m_filename = filename;
      m_file.open(filename, std::ios::out | std::ios::app);
}

void Logging::Logger::Log(LogLevel level, const std::string& message) {
      std::lock_guard<std::mutex> lock(m_lock_);
      std::string log_message = "[" + skynet::time::datetime() + "] " + message;
      std::cout << log_message << std::endl;
      LogFile(level, log_message);
}

void Logging::Logger::LogFile(LogLevel level, const std::string& message) {
      if (m_filename.empty()) {
            return;
      }
      
      if (!m_file.is_open()) {
            m_file.open(m_filename, std::ios::out | std::ios::app);
      }
      
      m_file << message << std::endl;
}

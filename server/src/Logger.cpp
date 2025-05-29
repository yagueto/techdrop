#include "Logger.h"
#include "Config.h"
#include <ctime>

Logger::Logger() = default;

Logger &Logger::get_logger() {
  static Logger logger;
  return logger;
}

void Logger::open() { log_file.open(Config::get_config().get_log_path()); }

Logger::~Logger() { close(); }

void Logger::write(const std::string &message) {
  if (!log_file.is_open()) {
    open();
  }
  log_file << std::time(nullptr) << " - " << message << std::endl;
}

void Logger::close() {
  if (log_file.is_open())
    log_file.close();
}

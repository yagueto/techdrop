#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>

#define LOG_PATH "server.log" // TODO: mover al config cuando esté implementado

class Logger {
  std::ofstream log_file;
  Logger();
  ~Logger();
  void open();

public:
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;
  static Logger &get_logger();
  void write(const std::string &message);
  void close();
};

#endif // LOGGER_H

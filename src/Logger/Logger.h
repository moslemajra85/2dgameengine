#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

enum LogType {
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR
};

struct LogEntry {

  LogType type;
  std::string message;
};

class Logger {

public:
  static std::vector<LogEntry> messages;
  static void Log(const std::string &message);
  static void Error(const std::string &message);
  static std::string CurrentDateTimeToString();
};

#endif
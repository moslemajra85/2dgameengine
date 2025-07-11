#include "Logger.h"
#include <chrono>
#include <format>
#include <iostream>
#include <string>


std::vector<LogEntry> Logger::messages;
void Logger::Log(const std::string &message) {

  LogEntry logEntry;
  logEntry.type = LOG_INFO;

  logEntry.message = "[" + CurrentDateTimeToString() + " " + message + "]";

  std::cout << "\033[32m" << logEntry.message << "\033[0m" << std::endl;
  Logger::messages.push_back(logEntry);
}

void Logger::Error(const std::string &message) {

  LogEntry logEntry;
  logEntry.type = LOG_ERROR;

  logEntry.message = "[ " + CurrentDateTimeToString() + " " + message + "]";
  std::cout << "\033[31m" << logEntry.message << "\033[0m" << std::endl;
  Logger::messages.push_back(logEntry);
}

std::string Logger::CurrentDateTimeToString() {
  // Get current system time
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);

  // Convert to tm structure
  std::tm tm{};
#if defined(_WIN32) || defined(_WIN64)
  localtime_s(&tm, &now_c);
#else
  localtime_r(&now_c, &tm);
#endif

  char buffer[11];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
  return std::string(buffer);
}

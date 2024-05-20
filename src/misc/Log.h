#pragma once

#include <string>
#include <chrono>

class Log {
public:
  Log() {};
  ~Log() {};

  static void Write(const std::string input);

  static void EndLine();
  static void StartLine();

  static void Save(const bool overwrite = true);

  static void StartTime();
  static bool CheckTime(const long long milliseconds);
  static bool CheckTimeSeconds(const double seconds);

private:
  static std::string m_console;
  static std::chrono::steady_clock::time_point m_time;
};
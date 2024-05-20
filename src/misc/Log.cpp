#include "Log.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

std::string Log::m_console = "";
std::chrono::steady_clock::time_point Log::m_time = std::chrono::high_resolution_clock::now();

void Log::Write(const std::string input) {
  std::cout << input;
  Log::m_console += input;
}

void Log::EndLine() {
  std::cout << '\n';
  Log::m_console += "\n";
}

void Log::StartLine() {
  std::time_t now = std::time(0);

  std::tm tmnow{};

  localtime_s(&tmnow, &now);
  typedef std::chrono::system_clock Clock;
  auto c_now = Clock::now();

  std::string month = std::to_string(tmnow.tm_mon + 1);
  month = month.size() == 1 ? "0" + month : month;

  std::string day = std::to_string(tmnow.tm_mday);
  day = day.size() == 1 ? "0" + day : day;

  std::string hour = std::to_string(tmnow.tm_hour);
  hour = hour.size() == 1 ? "0" + hour : hour;

  std::string min = std::to_string(tmnow.tm_min);
  min = min.size() == 1 ? "0" + min : min;

  // combine seconds and milliseconds
  std::string sec = std::to_string(tmnow.tm_sec);
  sec = sec.size() == 1 ? "0" + sec : sec;

  // get milliseconds
  const auto c_seconds = std::chrono::time_point_cast<std::chrono::seconds>(c_now);
  const auto c_fraction = c_now - c_seconds;
  const time_t c_cnow = Clock::to_time_t(c_now);
  const auto c_millisec = std::chrono::duration_cast<std::chrono::milliseconds>(c_fraction);
  const int c_millCount = int(c_millisec.count());

  std::string mil = std::to_string(c_millCount);
  while (mil.size() < 3) {
    mil = "0" + mil;
  }

  std::string line = std::to_string(tmnow.tm_year + 1900) + "-" + month + "-" + day + " "
    + hour + ":" + min + ":" + sec + "." + mil + " ";

  std::cout << line;
  Log::m_console += line;
}

void Log::Save(const bool overwrite) {
  std::fstream consoleLog;

  if (overwrite) {
    consoleLog.open("console.log", std::ios_base::out);
  }
  else {
    // checks if file exists
    consoleLog.open("console.log", std::ios_base::in);

    if (consoleLog.is_open()) {
      // file exist
      consoleLog.close();
      consoleLog.open("console.log", std::ios_base::app);
    }
    else {
      consoleLog.open("console.log", std::ios_base::out);
    }
  }

  consoleLog << Log::m_console;

  consoleLog.close();
}

void Log::StartTime() {
  Log::m_time = std::chrono::high_resolution_clock::now();
}

bool Log::CheckTime(const long long milliseconds) {
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - Log::m_time);
  return duration.count() >= milliseconds;
}

bool Log::CheckTimeSeconds(const double seconds) {
  return Log::CheckTime((long long)(std::ceil(seconds * 1000)));
}
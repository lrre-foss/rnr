#pragma once
#include <source_location>
#include <string>

namespace RNR {
class Logger {
public:
  static void LogMsg(std::string message,
                     std::source_location l = std::source_location::current());
};
} // namespace RNR

#define DEV_LOGMSGF(f...)                                                      \
  {                                                                            \
    static char tx[4096];                                                      \
    snprintf(tx, 4096, f);                                                     \
    RNR::Logger::LogMsg(tx);                                                   \
  }

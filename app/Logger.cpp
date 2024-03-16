#include "Logger.hpp"

namespace RNR {
void Logger::LogMsg(std::string message, std::source_location l) {
  printf("[%s:%i] %s\n", l.file_name(), l.line(), message.c_str());
}
} // namespace RNR
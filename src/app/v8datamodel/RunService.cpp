#include <v8datamodel/RunService.hpp>

namespace RNR {
  RunService::RunService() {
    paused = true;
    running = false;
  }

  void RunService::step() {
    sig_stepped.fire();
  }
}
#pragma once

#include <utility/Signal.hpp>

namespace RNR {
  class RunService {
    bool running;
    bool paused;
  public:
    RunService();

    void step();
    Signal<> sig_stepped;
  };
}
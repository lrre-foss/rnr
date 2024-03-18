#pragma once
#include <vector>
#include <functional>

namespace RNR {
  template<class... Args>
  class Signal {
    std::vector<std::function<void (Args...)>> listeners;
  public:
    void fire(Args... args) {
      for(auto l : listeners) {
        l(args...);
      }
    }

    void connect(std::function<void (Args...)> func) {
      listeners.push_back(func);
    }
  };
}
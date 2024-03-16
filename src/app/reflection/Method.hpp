#pragma once
#include <functional>
#include <string>
#include <reflection/Property.hpp>

namespace RNR::Reflection {
struct BaseMethod {
  std::string name;
  PropertyType returns;
  std::vector<PropertyType> args;
};

template <typename R, typename... A> class Method : BaseMethod {
  std::function<R(A...)> function;

public:
  Method(std::string name, PropertyType returns, std::vector<PropertyType> args,
         std::function<R(A...)> func) {
    this->name = name;
    this->returns = returns;
    this->function = func;
    this->args = args;
  }
};
} // namespace RNR::Reflection
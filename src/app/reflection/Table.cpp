#include "Table.hpp"
#include "Variant.hpp"

#include <Logger.hpp>

#include <map>
#include <stdexcept>

namespace RNR::Reflection {
Property *property(Variant *v, std::string name) {
  return v->getReflectionProperty(name);
}

std::vector<Property *> properties(Variant *v) {
  std::vector<Property *> p;
  auto m = v->getReflectionPropertyMap();
  for(auto ittr : m) {
    p.push_back(ittr.second);
  }
  return p;
}
} // namespace RNR::Reflection
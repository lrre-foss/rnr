#include "Variant.hpp"

namespace RNR::Reflection {
REFLECTION_BEGIN2(Variant);
REFLECTION_PROPERTY("Test", PT_STRING, test)
REFLECTION_END();

Variant::Variant() {
}

void Variant::reloadReflectionProperties() {
  if (reflection_properties.size() == 0)
    reflection_properties = getStaticInitProperties();
}

Reflection::Property *Variant::getReflectionProperty(std::string name) {
  reloadReflectionProperties();

  if (reflection_properties.find(name) != reflection_properties.end()) {
    return reflection_properties[name].get();
  } else {
    throw std::runtime_error("getReflectionProperty on invalid property");
  }
}

std::map<std::string, RNR::Reflection::Property *> Variant::getReflectionPropertyMap() {
  reloadReflectionProperties();
  
  std::map<std::string, RNR::Reflection::Property *> m;
  for (auto &&p : reflection_properties) {
    m[p.first] = p.second.get();
  }
  return m;
}
} // namespace RNR::Reflection
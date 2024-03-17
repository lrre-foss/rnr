#pragma once
#include <reflection/Table.hpp>

#define VARIANT_DEFINE(x)                             \
public:                                               \
  virtual const char *getType() const { return #x; }; \
  static const char *getTypeStatic() { return #x; }   \
                                                      \
private:

namespace RNR::Reflection {
class Variant {
  HAS_REFLECTION_TABLE;
  VARIANT_DEFINE(Variant)
  std::map<std::string, std::unique_ptr<RNR::Reflection::Property>> reflection_properties;
  void reloadReflectionProperties();

  std::string test;

public:
  RNR::Reflection::Property *getReflectionProperty(std::string name);
  std::map<std::string, RNR::Reflection::Property *> getReflectionPropertyMap();

  Variant();
};
} // namespace RNR::Reflection
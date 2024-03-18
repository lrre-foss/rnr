#pragma once
#include <cstring>
#include <reflection/Table.hpp>

#define VARIANT_DEFINE(x, i)                          \
public:                                               \
  virtual const char *getType() const { return #x; }; \
  static const char *getTypeStatic() { return #x; }   \
                                                      \
  virtual bool isA(const char *type) {                \
    if (std::strcmp(getType(), type) == 0)            \
      return true;                                    \
    return i::isA(type);                              \
  }                                                   \
                                                      \
private:
#define VARIANT_DEFINE2(x)                            \
public:                                               \
  virtual const char *getType() const { return #x; }; \
  static const char *getTypeStatic() { return #x; }   \
                                                      \
  virtual bool isA(const char *type) {                \
    if (std::strcmp(getType(), type) == 0)            \
      return true;                                    \
    return false;                                     \
  }                                                   \
                                                      \
private:

namespace RNR::Reflection {
class Variant {
  HAS_REFLECTION_TABLE;
  VARIANT_DEFINE2(Variant)
  std::map<std::string, std::unique_ptr<RNR::Reflection::Property>> reflection_properties;
  void reloadReflectionProperties();

  std::string test;

public:
  RNR::Reflection::Property *getReflectionProperty(std::string name);
  std::map<std::string, RNR::Reflection::Property *> getReflectionPropertyMap();

  Variant();
};
} // namespace RNR::Reflection
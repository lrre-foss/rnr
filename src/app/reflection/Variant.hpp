#pragma once
#include <reflection/Table.hpp>

#define VARIANT_DEFINE(x)                                                      \
public:                                                                        \
  virtual const char *getType() const { return #x; };                          \
  static const char *getTypeStatic() { return #x; }                            \
                                                                               \
private:

namespace RNR::Reflection {
class Variant {
  HAS_REFLECTION_TABLE;
  VARIANT_DEFINE(Variant)
};
} // namespace RNR::Reflection
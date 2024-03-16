#pragma once

#define VARIANT_DEFINE(x)                                                      \
public:                                                                        \
  virtual const char *getType() { return #x; };                                \
                                                                               \
private:

namespace RNR {
class Variant {
public:
  virtual const char *getType() { return "Variant"; };
};
} // namespace RNR
#pragma once
#include <cstddef>
#include <string>

namespace RNR::Reflection {
class Variant;

enum PropertyType {
  PT_STRING,
  PT_INTEGER, // must be int64 OR ELSE YOU DIE
  PT_NUMBER,
  PT_VARIANT,
};

class Property {
  std::string name;
  PropertyType type;

  void *offset;

public:
  // use offsetof to get the value for offset, ex offsetof(YourClass,
  // your_property)
  Property(std::string name, PropertyType type, void *offset) {
    this->name = name;
    this->type = type;
    this->offset = offset;
  }

  std::string getName() { return name; };
  PropertyType getType() { return type; };

  template <typename T>
  T *getData() { return (T *)offset; }
};
}; // namespace RNR::Reflection
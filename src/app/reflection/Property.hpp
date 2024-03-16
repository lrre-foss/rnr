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

struct BaseProperty {
  std::string name;
  PropertyType type;

  std::string getName() { return name; }; 
  PropertyType getType() { return type; };
};

template<typename C, typename T>
class Property : public BaseProperty {
  T* C::* offset;

public:
  // use offsetof to get the value for offset, ex offsetof(YourClass, your_property)
  Property(std::string name, PropertyType type, T* C::* offset) {
    this->name = name;
    this->type = type;
    this->offset = offset;
  }

  T* getData(Variant* v) {
    T* p = (T*)v + offset;
    return p;
  }
};
};
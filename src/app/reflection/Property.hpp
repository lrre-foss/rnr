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
  std::size_t offset;

public:
  // use offsetof to get the value for offset, ex offsetof(YourClass, your_property)
  Property(std::string name, PropertyType type, std::size_t offset);

  std::string getName() { return name; }; 
  PropertyType getType() { return type; };

  // please determine proper template to use by checking getType
  template<typename T> T* getData(Variant* v) {
    T* p = (T*)v + offset;
    return p;
  }
};
};
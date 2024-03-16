#include "Property.hpp"

namespace RNR::Reflection {
  Property::Property(std::string name, PropertyType type, std::size_t offset) {
    this->name = name;
    this->type = type;
    this->offset = offset;
  }

}
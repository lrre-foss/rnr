#include "BasePart.hpp"

namespace RNR {
  BasePart::BasePart() : PVInstance() {

  }
  
  REFLECTION_BEGIN(BasePart, PVInstance);
  REFLECTION_PROPERTY("Size", Reflection::PT_VECTOR3, size);
  REFLECTION_END();

  INSTANCE(BasePart);
}
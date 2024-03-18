#include "BasePart.hpp"

namespace RNR {
  BasePart::BasePart() : PVInstance() {
    size = glm::vec3(2,1,4);
    group_id = -1;
  }
  
  REFLECTION_BEGIN(BasePart, PVInstance);
  REFLECTION_PROPERTY("Size", Reflection::PT_VECTOR3, size);
  REFLECTION_END();

  INSTANCE(BasePart);
}
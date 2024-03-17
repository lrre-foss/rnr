#include "PVInstance.hpp"

namespace RNR {
  PVInstance::PVInstance() : Instance() {

  }

  REFLECTION_BEGIN(PVInstance, Instance);
  REFLECTION_PROPERTY("Position", Reflection::PT_VECTOR3, position);
  REFLECTION_PROPERTY("CFrame", Reflection::PT_MATRIX3X3, coordinate_frame);
  REFLECTION_END();

  INSTANCE(PVInstance);
}
#include "PVInstance.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RNR {
  PVInstance::PVInstance() : Instance() {

  }

  REFLECTION_BEGIN(PVInstance, Instance);
  REFLECTION_PROPERTY("Position", Reflection::PT_VECTOR3, position);
  REFLECTION_PROPERTY("CFrame", Reflection::PT_MATRIX3X3, coordinate_frame);
  REFLECTION_END();

  INSTANCE(PVInstance);


  glm::mat4 PVInstance::makeTransform() {
    glm::mat4 t = glm::mat4(1.0);
    t *= glm::mat4(coordinate_frame);
    t = glm::translate(t, position);
    return t;
  }
}
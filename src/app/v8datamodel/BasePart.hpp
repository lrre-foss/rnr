#pragma once
#include <v8datamodel/PVInstance.hpp>

namespace RNR {
  class BasePart : public PVInstance {
    HAS_REFLECTION_TABLE;
    VARIANT_DEFINE(BasePart);

    glm::vec3 size;
  public:
    BasePart();
  };
}
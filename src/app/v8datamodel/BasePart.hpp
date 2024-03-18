#pragma once
#include <v8datamodel/PVInstance.hpp>

namespace RNR {
  class BasePart : public PVInstance {
    HAS_REFLECTION_TABLE;
    VARIANT_DEFINE(BasePart, PVInstance);

    glm::vec3 size;
    int group_id;
  public:
    BasePart();

    int getGroupId() { return group_id; };
    // for BrickMongler
    void setGroupId(int id) { group_id = id; }
  };
}
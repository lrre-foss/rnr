#include <v8tree/Instance.hpp>
#include <glm/glm.hpp>

namespace RNR {
  class PVInstance : public Instance {
    HAS_REFLECTION_TABLE;
    VARIANT_DEFINE(PVInstance);

    glm::mat3 coordinate_frame;
    glm::vec3 position;
  public:
    PVInstance();
  };
}
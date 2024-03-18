#pragma once
#include <v8datamodel/Model.hpp>
#include <v8datamodel/BasePart.hpp>
#include <glm/glm.hpp>

namespace RNR::Rendering {
  struct BrickGroup {
    std::vector<BasePart*> parts;
    BasePart* primary_part;

    unsigned int gl_buffer;
    bool dirty;
  };

  struct BrickVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
  };

  struct BrickMesh {
    std::vector<BrickVertex> vertices;
    std::vector<int> indices;
  };

  class BrickMongler {
    Model* model;

    BrickGroup anchored_group;
    std::map<int, BrickGroup> groups;

    void newPart(Instance* i);
    void remPart(Instance* i);
    void newJoint(BasePart* a, BasePart* b);

    void iterateThroughModel(Model* model);

    BrickMesh createBrickMesh(BasePart* part);
    void addMeshToGroup(BrickGroup* group);
  public:
    BrickMongler(Model* model);
    
    void updateBricks();
  };
}
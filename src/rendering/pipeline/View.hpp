#pragma once
#include <glm/glm.hpp>
#include <v8datamodel/Model.hpp>

namespace RNR::Rendering {
  class View {
    glm::vec4 viewport;
    Model* model;
  public:
    View();

    void setModel(Model* m) { model = m; }

    glm::vec4 getViewport() { return viewport; }
    void setViewport(glm::vec4 vp) { viewport = vp; }

    void frame();
  };
};
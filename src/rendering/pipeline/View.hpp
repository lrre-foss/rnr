#pragma once
#include <glm/glm.hpp>
#include <v8datamodel/Model.hpp>
#include <pipeline/BrickMongler.hpp>

namespace RNR::Rendering {
  class View {
    glm::vec4 viewport;
    Model* model;
    BrickMongler* mongler;
  public:
    View();

    void setModel(Model* m) { model = m; }

    glm::vec4 getViewport() { return viewport; }
    void setViewport(glm::vec4 vp) { viewport = vp; }

    void frame();
    Signal<> sig_frame;
  };
};
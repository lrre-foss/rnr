#include "View.hpp"
#include <glad/glad.h>

namespace RNR::Rendering {
  View::View() {
    viewport = glm::vec4(0, 0, 640, 480);
  }

  void View::frame() {
    glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
    glClearColor(0.4,0.4,0.4,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render stuff

  }
}
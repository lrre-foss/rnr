#pragma once
#include <v8datamodel/Model.hpp>

namespace RNR::Rendering {
  struct BrickGroup {
    
  };
  class BrickMongler {
    Model* m;
  public:
    BrickMongler(Model* model);

    void updateBricks();
  };
}
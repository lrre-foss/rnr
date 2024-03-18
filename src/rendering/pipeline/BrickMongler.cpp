#include "BrickMongler.hpp"

namespace RNR::Rendering {
  BrickMongler::BrickMongler(Model* model) {
    this->model = model;
    model->sig_onDescendantAdded.connect([this](Instance* i){newPart(i);});
    model->sig_onDescendantRemoved.connect([this](Instance* i){remPart(i);});
    updateBricks();
  }

  void BrickMongler::newPart(RNR::Instance* instance) {

  }

  void BrickMongler::remPart(RNR::Instance* instance) {
    
  }

  void BrickMongler::updateBricks() {
    iterateThroughModel(model);

    for(auto it : groups) {
      if(it.second.dirty) {
        // update mesh
        it.second.dirty = false;
      }
    }
  }

  void BrickMongler::iterateThroughModel(Model* model) {
    auto children = model->getChildren();
    for(auto child : children) {
      if(child->isA(BasePart::getTypeStatic())) {
        BasePart* part = dynamic_cast<BasePart*>(child);
        int bg = part->getGroupId();

      } else if(child->isA(Model::getTypeStatic())) {
        iterateThroughModel(model);
      }
    }
  }
}
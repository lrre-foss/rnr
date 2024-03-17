#include "Model.hpp"

namespace RNR {
  Model::Model() : Instance() {
    primary_part = nullptr;
  }

  REFLECTION_BEGIN(Model, Instance);
  REFLECTION_PROPERTY("PrimaryPart", Reflection::PT_VARIANT, primary_part);
  REFLECTION_END();

  INSTANCE(Model);
}
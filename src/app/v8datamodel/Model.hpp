#pragma once
#include <v8tree/Instance.hpp>

namespace RNR {
  class Model : public Instance {
    HAS_REFLECTION_TABLE;
    VARIANT_DEFINE(Model, Instance);

    Instance* primary_part;

  public:
    Model();
  };
};
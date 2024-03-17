#include "Instance.hpp"
#include <Logger.hpp>

namespace RNR {
Instance::Instance() {
  name = getType();
  parent = nullptr;
  datamodel = nullptr;
}

REFLECTION_BEGIN(Instance, Reflection::Variant);
REFLECTION_PROPERTY("Parent", Reflection::PT_VARIANT, parent);
REFLECTION_PROPERTY("Name", Reflection::PT_STRING, name);
REFLECTION_END();

INSTANCE(Instance);

void Instance::setParent(Instance *new_parent) {
  if(parent)
    parent->removeChild(this);
  if(new_parent)
    new_parent->addChild(this);
  else
    parent = 0;
}

bool Instance::removeChild(Instance *child) {
  int i;
  auto it = std::find(children.begin(), children.end(), child);
  if(it != children.end()) {
    size_t index = std::distance(children.begin(), it);
    children[index]->parent = nullptr;
    children.erase(it);
    return true;
  }
  return false;
}

void Instance::addChild(Instance* new_child) {
  children.push_back(new_child);
  new_child->parent = this;
}

std::unique_ptr<Instance> InstanceFactory::create(std::string type) {
  auto it = constructors.find(type);
  if (it != constructors.end()) {
    Instance *ins = constructors[type]();
    return std::unique_ptr<Instance>(ins);
  } else {
    throw std::runtime_error("Attempt to create invalid instance type");
  }
}

void InstanceFactory::addConstructor(std::string type, InstanceConstructor ctor) {
  DEV_LOGMSGF("added constructor for %s", type.c_str());
  constructors[type] = ctor;
}
} // namespace RNR
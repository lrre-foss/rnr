#include "Instance.hpp"
#include <Logger.hpp>

namespace RNR {
REFLECTION_BEGIN(Instance);
REFLECTION_PROPERTY(Instance, "Parent", Reflection::PT_VARIANT, parent);
REFLECTION_PROPERTY(Instance, "Name", Reflection::PT_STRING, name);
REFLECTION_END();

Instance::Instance() {
  parent = nullptr;
  datamodel = nullptr;
}

void Instance::setParent(Instance *new_parent) {
  if (!new_parent) {
    if (parent)
      parent->removeChild(this);
  }
  if (parent) {
    new_parent->addChild(parent->removeChild(this));
  } else {
    new_parent->addChild(std::unique_ptr<Instance>(this));
  }
}

std::unique_ptr<Instance> Instance::removeChild(Instance *child) {
  int i;
  for (i = 0; i < children.size(); i++) {
    if (child == children[i].get()) {
      break;
    }
  }
  std::unique_ptr<Instance> old_ref = std::move(children[i]);
  children[i]->parent = nullptr;
  children.erase(children.begin() + i);
  return old_ref;
}

void Instance::addChild(std::unique_ptr<Instance> new_child) {
  children.push_back(std::move(new_child));
  new_child->parent = this;
}

std::map<std::string, InstanceConstructor> InstanceFactory::constructors;
std::unique_ptr<Instance> InstanceFactory::create(std::string type) {
  auto it = constructors.find(type);
  if (it != constructors.end()) {
    Instance *ins = constructors[type]();
    return std::unique_ptr<Instance>(ins);
  } else {
    throw std::runtime_error("Attempt to create invalid instance type");
  }
}
} // namespace RNR
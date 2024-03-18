#pragma once
#include <stdexcept>
#include <memory>
#include <vector>
#include <functional>
#include <map>

#include <utility/Signal.hpp>
#include <reflection/Variant.hpp>

namespace RNR {
class DataModel;

class Instance : public Reflection::Variant {
  HAS_REFLECTION_TABLE;
  VARIANT_DEFINE(Instance, Reflection::Variant)

  DataModel* datamodel;
  Instance* parent;
  std::string name;
  std::vector<Instance*> children;

public:
  Instance();
  virtual ~Instance() = default;

  void onDescendantRemoved(Instance* instance);
  Signal<Instance*> sig_onDescendantRemoved;
  void onDescendantAdded(Instance* instance);
  Signal<Instance*> sig_onDescendantAdded;

  /**
   * @brief this will set the parent of Instance to newparent
   * 
   * @param newparent the new parent
   */
  void setParent(Instance* newparent);

  /**
   * @brief removes instance from children
   * 
   * @param child 
   * @return if child was removed
   */
  bool removeChild(Instance* child);

  /**
   * @brief adds a new child this will snatch ownership
   * 
   * @param new_child 
   */
  void addChild(Instance* new_child);

  std::vector<Instance*> getChildren() { return children; }
};

typedef std::function<Instance* ()> InstanceConstructor;

class InstanceFactory {
  static std::map<std::string, InstanceConstructor> constructors;
public:
  static std::unique_ptr<Instance> create(std::string type);
  static void addConstructor(std::string type, InstanceConstructor constructor);
};


#define INSTANCE(x) InstanceFactoryInit<x> __ifi_##x = InstanceFactoryInit<x> ();

template<typename T> class InstanceFactoryInit {
  static_assert(std::is_base_of<Instance, T>::value, "T must derive from Instance");

public:
  InstanceFactoryInit() {
    InstanceFactory::addConstructor(T::getTypeStatic(), constructor);
  }

  static T* constructor() {
    T* t = new T();
    return t;
  }
};
} // namespace RNR
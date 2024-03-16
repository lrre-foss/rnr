#pragma once
#include <reflection/Property.hpp>
#include <reflection/Method.hpp>
#include <vector>

// do not ever call addTableEntries as it will be automagically called for you
#define HAS_REFLECTION_TABLE                                                   \
public:                                                                        \
  static void addTableEntries();                                               \
                                                                               \
private:

#define REFLECTION_BEGIN(c)                                                    \
  static RNR::Reflection::InitTable<c> __initTable__##c;                       \
  void c::addTableEntries() {                                                  \
    std::string _t = c::getTypeStatic();
// lol
#define REFLECTION_END() }

// c is class, n is name, t is PropertyType, p is property
#define REFLECTION_PROPERTY(c, n, t, p)                                        \
  RNR::Reflection::__addNewTableProperty(                                      \
      _t, new RNR::Reflection::Property(n, t, offsetof(c, p)));

namespace RNR::Reflection {
void __addNewTableProperty(std::string type, Property *p);
void __addNewTableMethod(std::string type, BaseMethod* m);
Property *property(Variant *v, std::string name);
std::vector<Property *> properties(Variant *v);

template <typename T> class InitTable {
public:
  InitTable() { T::addTableEntries(); }
};
} // namespace RNR::Reflection
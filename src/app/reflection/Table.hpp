#pragma once
#include <map>
#include <memory>
#include <reflection/Method.hpp>
#include <reflection/Property.hpp>
#include <string>
#include <vector>

#define HAS_REFLECTION_TABLE                                                                           \
protected:                                                                                             \
  virtual std::map<std::string, std::unique_ptr<RNR::Reflection::Property>> getStaticInitProperties(); \
                                                                                                       \
private:

// c is class name, i is class c inherits from
#define REFLECTION_BEGIN(c, i)                                                                                      \
  std::map<std::string, std::unique_ptr<RNR::Reflection::Property>>                                                 \
  c::getStaticInitProperties() {                                                                                    \
    std::map<std::string, std::unique_ptr<RNR::Reflection::Property>> table_entries = i::getStaticInitProperties(); \
    ;
#define REFLECTION_BEGIN2(c)                                        \
  std::map<std::string, std::unique_ptr<RNR::Reflection::Property>> \
  c::getStaticInitProperties() {                                    \
    std::map<std::string, std::unique_ptr<RNR::Reflection::Property>> table_entries;
// lol
#define REFLECTION_END() \
  return table_entries;  \
  }

// n is name, t is PropertyType, , p is property
#define REFLECTION_PROPERTY(n, t, p) table_entries[n] = std::unique_ptr<RNR::Reflection::Property>(new RNR::Reflection::Property(n, t, &p));

namespace RNR::Reflection {
void __addNewTableProperty(std::string type, Property *p);
void __addNewTableMethod(std::string type, BaseMethod *m);
Property *property(Variant *v, std::string name);
std::vector<Property *> properties(Variant *v);
} // namespace RNR::Reflection
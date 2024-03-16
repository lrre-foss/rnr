#include "Table.hpp"
#include "Variant.hpp"

#include <Logger.hpp>

#include <map>
#include <stdexcept>

namespace RNR::Reflection {
class Table {
  std::map<std::string, BaseProperty *> properties;

public:
  std::map<std::string, BaseProperty *> getProperties() { return properties; }

  BaseProperty *getPropertyByName(std::string n) {
    if (properties.find(n) == properties.end())
      throw std::runtime_error("Invalid property name");
    return properties[n];
  }

  void addProperty(BaseProperty *p) {
    properties[p->getName()] = p;
  }
};

std::map<std::string, Table> tables;

void __addNewTableProperty(std::string type, BaseProperty *p) {
  if (tables.find(type) == tables.end()) {
    tables[type] = Table();
  }
  tables[type].addProperty(p);
}

BaseProperty *property(Variant *v, std::string name) {
  if (tables.find(v->getType()) == tables.end())
    throw std::runtime_error("Can't find variant in tables");
  Table &t = tables[v->getType()];
  BaseProperty *p = t.getPropertyByName(name);
  return p;
}

std::vector<BaseProperty *> properties(Variant *v) {
  if (tables.find(v->getType()) == tables.end())
    throw std::runtime_error("Can't find variant in tables");
  Table &t = tables[v->getType()];
  std::vector<BaseProperty *> p;
  for (auto it : t.getProperties())
    p.push_back(it.second);
  return p;
}
} // namespace RNR::Reflection
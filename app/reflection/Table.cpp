#include "Table.hpp"
#include "Variant.hpp"

#include <Logger.hpp>

#include <map>
#include <stdexcept>

namespace RNR::Reflection {
class Table {
  std::map<std::string, Property *> properties;

public:
  std::map<std::string, Property *> getProperties() { return properties; }

  Property *getPropertyByName(std::string n) {
    if (properties.find(n) == properties.end())
      throw std::runtime_error("Invalid property name");
    return properties[n];
  }

  void addProperty(Property *p) {
    properties[p->getName()] = p;
  }
};

std::map<std::string, Table> tables;

void __addNewTableProperty(std::string type, Property *p) {
  if (tables.find(type) == tables.end()) {
    tables[type] = Table();
  }
  tables[type].addProperty(p);
}

Property *property(Variant *v, std::string name) {
  if (tables.find(v->getType()) == tables.end())
    throw std::runtime_error("Can't find variant in tables");
  Table &t = tables[v->getType()];
  Property *p = t.getPropertyByName(name);
  return p;
}

std::vector<Property *> properties(Variant *v) {
  if (tables.find(v->getType()) == tables.end())
    throw std::runtime_error("Can't find variant in tables");
  Table &t = tables[v->getType()];
  std::vector<Property *> p;
  for (auto it : t.getProperties())
    p.push_back(it.second);
  return p;
}
} // namespace RNR::Reflection
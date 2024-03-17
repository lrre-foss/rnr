#include "Instance.hpp"

namespace RNR {
  // this is so this will be statically initialized before everything else
  // idk if theres a better way to  do this
  std::map<std::string, InstanceConstructor> InstanceFactory::constructors;
}

#pragma once
#include <memory>
#include <vector>

namespace RNR {
class Instance {
  Instance* parent;
  std::vector<std::unique_ptr<Instance>> children;

public:
  Instance();

  /**
   * @brief this will set the parent of Instance to newparent
   * newparent will take ownership of this
   * 
   * @param newparent the new parent
   */
  void setParent(Instance* newparent);

  /**
   * @brief removes instance from children, ownership of the instance will be given to caller
   * 
   * @param child 
   * @return std::unique_ptr<Instance> 
   */
  std::unique_ptr<Instance> removeChild(Instance* child);

  /**
   * @brief adds a new child 
   * 
   * @param new_child 
   */
  void addChild(std::unique_ptr<Instance> new_child);
};
} // namespace RNR
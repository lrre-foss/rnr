#include "Instance.hpp"

void RBX::Instance::setName(std::string name)
{
    if(name != this->m_name)
    {
        this->m_name = name;
        // raise property changed
    }
}
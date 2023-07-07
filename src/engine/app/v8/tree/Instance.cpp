#include <engine/app/v8/tree/Instance.hpp>
#include <stdexcept>

RBX::Instance::Instance()
{

}

RBX::Instance::Instance(std::string name)
{

}

bool RBX::Instance::contains(RBX::Instance* child)
{

}

bool RBX::Instance::isAncestorOf(RBX::Instance* instance)
{
    
}

bool RBX::Instance::askSetParent(RBX::Instance* instance)
{
    return true;
}

bool RBX::Instance::canSetParent(RBX::Instance* instance)
{
    return !instance || instance->canAddChild(this);
}

bool RBX::Instance::askAddChild(RBX::Instance* instance)
{
    return true;
}

bool RBX::Instance::canAddChild(RBX::Instance* instance)
{
    if(instance->contains(this) || instance->m_parent == this)
        return false;
    if(askAddChild(instance))
        return true;
    return instance->askSetParent(this);
}

void RBX::Instance::setName(std::string name)
{
    if(name != this->m_name)
    {
        this->m_name = name;
        // raise property changed
    }
}

void RBX::Instance::setParent(RBX::Instance* newParent)
{
    if(newParent != m_parent)
    {
        char error_text[255];
        if(this == newParent)
        {
            snprintf(error_text, 255, "Attempt to set %s as its own parent", m_name);
            throw std::runtime_error(error_text);
        }
        if(isAncestorOf(newParent))
        {
            snprintf(error_text, 255, "Attempt to set parent of %s to %s results in circular reference", newParent->getName(), m_name);
            throw std::runtime_error(error_text);
        }

        if(m_parent)
        {
            std::vector<boost::shared_ptr<RBX::Instance>>* children = m_parent->getChildren();
            auto child_it = std::find(children->begin(), children->end(), (boost::shared_ptr<RBX::Instance>)this);            
            if(child_it != children->end())
                children->erase(child_it);
            if(m_parent->numChildren() == 0)
            {
                // signal onlastchildremoved
            }
        }

        m_parent = newParent;
        m_parent->m_children.push_back((boost::shared_ptr<RBX::Instance>)this);
        newParent->onChildAdded(this);
    }
}

void RBX::Instance::onChildAdded(RBX::Instance* childAdded)
{

}
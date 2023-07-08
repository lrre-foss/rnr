#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    Instance::Instance()
    {
        //
    }

    Instance::Instance(std::string name)
    {
        //
    }

    bool Instance::contains(RNR::Instance* child)
    {
        auto child_it = std::find(m_children.begin(), m_children.end(), (boost::shared_ptr<RNR::Instance>)child);            

        return child_it != m_children.end();
    }

    bool RNR::Instance::isAncestorOf(RNR::Instance* instance)
    {
        RNR::Instance* instance_parent = instance->m_parent;
        while (instance_parent != 0)
        {
            instance_parent = instance_parent->m_parent;

            if (instance_parent == this)
                return true;
        }

        return false;
    }

    bool RNR::Instance::askSetParent(RNR::Instance* instance)
    {
        return true;
    }

    bool RNR::Instance::canSetParent(RNR::Instance* instance)
    {
        return !instance || instance->canAddChild(this);
    }

    bool RNR::Instance::askAddChild(RNR::Instance* instance)
    {
        return true;
    }

    bool RNR::Instance::canAddChild(RNR::Instance* instance)
    {
        if (instance->contains(this) || instance->m_parent == this)
            return false;
        
        if (askAddChild(instance))
            return true;
        
        return instance->askSetParent(this);
    }

    void RNR::Instance::setName(std::string name)
    {
        if (name != this->m_name)
        {
            this->m_name = name;
            // raise property changed
        }
    }

    void RNR::Instance::setParent(RNR::Instance* newParent)
    {
        if (newParent != m_parent)
        {
            char error_text[255];
            if (this == newParent)
            {
                snprintf(error_text, 255, "Attempt to set %s as its own parent", m_name);
                throw std::runtime_error(error_text);
            }
            if (isAncestorOf(newParent))
            {
                snprintf(error_text, 255, "Attempt to set parent of %s to %s results in circular reference", newParent->getName(), m_name);
                throw std::runtime_error(error_text);
            }

            if (m_parent)
            {
                std::vector<boost::shared_ptr<RNR::Instance>>* children = m_parent->getChildren();
                auto child_it = std::find(children->begin(), children->end(), (boost::shared_ptr<RNR::Instance>)this);

                if (child_it != children->end())
                    children->erase(child_it);
                
                if (m_parent->numChildren() == 0)
                {
                    // signal onlastchildremoved
                }
            }

            m_parent = newParent;
            m_parent->m_children.push_back((boost::shared_ptr<RNR::Instance>)this);
            newParent->onChildAdded(this);
        }
    }

    void RNR::Instance::onChildAdded(RNR::Instance* childAdded)
    {
        //
    }
}
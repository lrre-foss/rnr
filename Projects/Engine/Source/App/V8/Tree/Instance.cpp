#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    World* Instance::world = 0;

    Instance::Instance()
    {
        m_node = 0;
        m_object = 0;
        m_parent = 0;
        setName("Instance");
    }

    Instance::~Instance()
    {
        setParent(NULL);
    }

    std::vector<ReflectionProperty> Instance::getProperties()
    {
        ReflectionProperty properties[]  = {
            { this, std::string("Name"), std::string("This is the name of this Instance."), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_STD_STRING,         
              REFLECTION_GETTER(Instance* instance = (Instance*)object; return &instance->m_name; ), 
              REFLECTION_SETTER(Instance* instance = (Instance*)object; instance->setName(*(std::string*)value); ) },

            { this, std::string("Parent"), std::string("This is the parent of this Instance."), 
              ACCESS_NONE, OPERATION_READ, PROPERTY_INSTANCE,         
              REFLECTION_GETTER(Instance* instance = (Instance*)object; return instance->m_parent; ), 
              REFLECTION_NO_SETTER() },

            { this, std::string("Archivable"), std::string("This determines whether this Instance may be saved or replicated."), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_BOOL,         
              REFLECTION_GETTER(Instance* instance = (Instance*)object; return &instance->m_archivable; ), 
              REFLECTION_SETTER(Instance* instance = (Instance*)object; instance->m_archivable = *(bool*)value; ) },
        };

        std::vector<ReflectionProperty> _properties(properties, properties+(sizeof(properties)/sizeof(ReflectionProperty)));
        addProperties(_properties);

        return _properties;
    }

    void Instance::deserializeXmlProperty(pugi::xml_node prop)
    {
        pugi::xml_attribute prop_name = prop.attribute("name");
        if(prop_name.as_string() == std::string("Name"))
            setName(prop.text().as_string());
        else
            deserializeProperty((char*)prop_name.as_string(), prop);
    }

    bool Instance::contains(Instance* child)
    {
        auto child_it = std::find(m_children.begin(), m_children.end(), child);            

        return child_it != m_children.end();
    }

    bool Instance::isAncestorOf(Instance* instance)
    {
        Instance* instance_parent = instance->m_parent;
        while (instance_parent != 0)
        {
            instance_parent = instance_parent->m_parent;

            if (instance_parent == this)
                return true;
        }

        return false;
    }

    bool Instance::askSetParent(Instance* instance)
    {
        return true;
    }

    bool Instance::canSetParent(Instance* instance)
    {
        return !instance || instance->canAddChild(this);
    }

    bool Instance::askAddChild(Instance* instance)
    {
        return true;
    }

    bool Instance::canAddChild(Instance* instance)
    {
        if (instance->contains(this) || instance->m_parent == this)
            return false;
        
        if (askAddChild(instance))
            return true;
        
        return instance->askSetParent(this);
    }

    void Instance::setName(std::string name)
    {
        if (name != this->m_name)
        {
            this->m_name = name;
            // raise property changed
        }
    }

    void Instance::setParent(Instance* newParent)
    {
        if (newParent != m_parent)
        {
            char error_text[255];
            if (this == newParent)
            {
                snprintf(error_text, 255, "Attempt to set %s as its own parent", m_name.c_str());
                throw std::runtime_error(error_text);
            }
            if (isAncestorOf(newParent))
            {
                snprintf(error_text, 255, "Attempt to set parent of %s to %s results in circular reference", newParent->getName().c_str(), m_name.c_str());
                throw std::runtime_error(error_text);
            }

            if (m_parent)
            {
                std::vector<Instance*>* children = m_parent->getChildren();
                auto child_it = std::find(children->begin(), children->end(), this);

                if (child_it != children->end())
                {
                    children->erase(child_it);
                    m_parent->onChildRemoved(this);
                
                    if (m_parent->numChildren() == 0)
                    {
                        // signal onlastchildremoved
                    }
                }
            }

            m_parent = newParent;
            if(m_parent)
            {
                m_parent->m_children.push_back(this);
                newParent->onChildAdded(this);
            }
        }
    }

    void Instance::onChildAdded(Instance* childAdded)
    {
        //
    }


    void Instance::onChildRemoved(RNR::Instance* childRemoved)
    {
        
    }

    bool Instance::isA(std::string type)
    {
        if (type == getClassName())
            return true; // TODO: check if type is any of parent types
        return false;
    }

    Instance* Instance::findFirstChild(std::string name)
    {
        for(auto& child : m_children)
        {
            if(child->getName() == name)
                return child;
        }
        return NULL;
    }

    Instance* Instance::findFirstChildOfType(std::string type)
    {
        for(auto& child : m_children)
        {
            if(child->isA(type))
                return child;
        }
        return NULL;
    }
}
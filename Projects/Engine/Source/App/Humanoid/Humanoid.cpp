#include <App/Humanoid/Humanoid.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    Humanoid::Humanoid()
    {
        //
    }

    Humanoid::~Humanoid()
    {
        //
    }

    bool Humanoid::canSit()
    {
        return true;
    }

    void Humanoid::buildJoints()
    {
        //
    }

    void Humanoid::checkForJointDeath()
    {
        //
    }

    void Humanoid::computeForce(float force, bool throttling)
    {
        //
    }

    void Humanoid::createHealthBar()
    {
        if(!getHead())
        {
            printf("Humanoid::createHealthBar: no head\n");
            return;
        }
        if(getNode())
            world->getOgreSceneManager()->destroySceneNode(getNode());
        setNode(world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode());
        Ogre::BillboardSet* healthBarSet = world->getOgreSceneManager()->createBillboardSet("HumanoidHealth" + getParent()->getName());
        Ogre::Billboard* healthBarBillboard = healthBarSet->createBillboard(Ogre::Vector3(100, 0, 200));
        getNode()->attachObject(healthBarSet);
        getNode()->setPosition(getHead()->getPosition());

        printf("Humanoid::createHealthBar: WIP");
    }

    void Humanoid::deserializeProperty(char* prop_name, pugi::xml_node prop)
    {
        if(prop_name == std::string("Health"))
        {
            setHealth(prop.text().as_float());
        }
        else if(prop_name == std::string("MaxHealth"))
        {
            setMaxHealth(prop.text().as_float());
        }
    }

    void Humanoid::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("Health"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_FLOAT,         
              REFLECTION_GETTER(Humanoid* instance = (Humanoid*)object; return &instance->m_health; ), 
              REFLECTION_SETTER(Humanoid* instance = (Humanoid*)object; instance->setHealth(*(float*)value); ) },
            { this, std::string("MaxHealth"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_FLOAT,         
              REFLECTION_GETTER(Humanoid* instance = (Humanoid*)object; return &instance->m_maxHealth; ), 
              REFLECTION_SETTER(Humanoid* instance = (Humanoid*)object; instance->setMaxHealth(*(float*)value); ) },
        };

        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }

    PartInstance* Humanoid::getTorso()
    {
        return (PartInstance*)getParent()->findFirstChild("Torso");
    }

    PartInstance* Humanoid::getHead()
    {
        return (PartInstance*)getParent()->findFirstChild("Head");
    }
}
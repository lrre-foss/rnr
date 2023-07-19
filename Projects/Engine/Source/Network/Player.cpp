#include <Network/Player.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    Player::Player()
    {
        setName("Player");
        setParent(world->getDatamodel()->getService("Players"));

        m_character = NULL;
    }

    void Player::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("Character"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_INSTANCE,         
              REFLECTION_GETTER(Player* instance = (Player*)object; return instance->m_character; ), 
              REFLECTION_SETTER(Player* instance = (Player*)object; instance->setCharacter((ModelInstance*)value); ) },
        };

        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }
}

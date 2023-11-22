#include <App/Humanoid/Humanoid.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/World/Weld.hpp>
#include <App/InputManager.hpp>
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include <Helpers/Bullet.hpp>

namespace RNR
{
    Humanoid::Humanoid()
    {
        setName("Humanoid");

        m_maxHealth = 100.f;
        m_health = 100.f;
        m_walkSpeed = 16.f;
    }

    void Humanoid::lateInit()
    {
        btBoxShape* playerShape = new btBoxShape(btVector3(1,2,0.5));
        m_playerGhostObject = new btPairCachingGhostObject();
        world->getDynamicsWorld()->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

        m_playerGhostObject->setCollisionShape(playerShape);
        m_playerGhostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

        m_characterController = new btKinematicCharacterController(m_playerGhostObject, playerShape, 0.5, btVector3(0.0, 1.0, 0.0));
    }

    Humanoid::~Humanoid()
    {
        //
    }

    bool Humanoid::canSit()
    {
        return true;
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
        if(!world)
            return;
        if(!world->getHasRender())
            return;
        if(!getHead())
        {
            printf("Humanoid::createHealthBar: no head\n");
            return;
        }
        if(getNode())
            world->getOgreSceneManager()->destroySceneNode(getNode());

        setNode(world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode());
        Ogre::BillboardSet* healthBarSet = world->getOgreSceneManager()->createBillboardSet("HumanoidHealth" + getParent()->getName());
        healthBarSet->setBillboardType(Ogre::BillboardType::BBT_PERPENDICULAR_COMMON);
        healthBarSet->setDebugDisplayEnabled(true);
        //Ogre::Billboard* healthBarBillboard = healthBarSet->createBillboard(Ogre::Vector3(0, 2, 0), Ogre::ColourValue(1, 0, 0, 1));
        Ogre::Billboard* healthBarBillboardFilled = healthBarSet->createBillboard(Ogre::Vector3(0, 2, 0), Ogre::ColourValue(0, 1, 0, 1));
        float healthBarScale = 0.5f;
        //healthBarBillboard->setDimensions(5 * healthBarScale, 1 * healthBarScale);
        healthBarBillboardFilled->setDimensions((m_health / m_maxHealth) * 5.f * healthBarScale, 1 * healthBarScale);
        healthBarSet->setCastShadows(true);

        Ogre::BillboardSet* nameBarSet = world->getOgreSceneManager()->createBillboardSet("HumanoidName" + getParent()->getName());        
        nameBarSet->setDebugDisplayEnabled(true);
        Ogre::FontPtr comic = Ogre::FontManager::getSingletonPtr()->getByName("ComicSans");
        if(!comic)
            printf("Humanoid::createHealthBar: comic == NULL\n");
        comic->putText(nameBarSet, getParent()->getName(), 1);
        int num_billboards = nameBarSet->getNumBillboards();
        for(int i = 0; i < num_billboards; i++)
        {
            Ogre::Billboard* chara = nameBarSet->getBillboard(i);
            Ogre::Vector3 chara_pos = chara->getPosition();
            chara_pos.y += 2 + healthBarScale;
            chara->setPosition(chara_pos);
        }
        getNode()->attachObject(healthBarSet);
        getNode()->attachObject(nameBarSet);
        getNode()->setPosition(getHead()->getPosition());
        getNode()->setOrientation(getHead()->getRotation());

        printf("Humanoid::createHealthBar: WIP\n");
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

    void Humanoid::inputFrame(float dx, float dy)
    {
        IInputManager* inputManager = world->getInputManager();
        Camera* camera = world->getWorkspace()->getCurrentCamera();
        if(inputManager)
        {
            Ogre::Matrix3 camera_rotation;
            camera_rotation.FromEulerAnglesYXZ(camera->getYaw(), Ogre::Radian(0), Ogre::Radian(0)); // we only want yaw because otherwise the movement target will go through the ground/in the air
            float forward = 0;
            Ogre::Vector3 move = Ogre::Vector3(0,0,0);

            if(inputManager->isKeyDown('W'))
                move += Ogre::Vector3(0, 0, m_walkSpeed);
            if(inputManager->isKeyDown('S'))
                move += Ogre::Vector3(0, 0, -m_walkSpeed);
            if(inputManager->isKeyDown('A'))
                move += Ogre::Vector3(m_walkSpeed, 0, 0);
            if(inputManager->isKeyDown('D'))
                move += Ogre::Vector3(-m_walkSpeed, 0, 0);

            m_characterController->setWalkDirection(Bullet::v3ToBullet(move));

            if(getTorso())
            {
                getTorso()->getCFrame().setPosition(Bullet::v3ToOgre(m_playerGhostObject->getWorldTransform().getOrigin()));
                getTorso()->updateMatrix();
            }

            if(getHead() && camera)
            {
                CoordinateFrame focus_cframe = getHead()->getCFrame();

                camera->setSubject(getHead());
                camera->setFocus(focus_cframe);
                camera->cameraFrame(dx, dy, true);
            }
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
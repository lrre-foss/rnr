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
        
        btBoxShape* playerShape = new btBoxShape(btVector3(1,2,0.5));
        m_playerGhostObject = new btPairCachingGhostObject();
        world->getDynamicsWorld()->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

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

    void Humanoid::buildJoints()
    {
        if(getTorso())
        {
            btTransform ghostTransform;
            ghostTransform.setIdentity();
            ghostTransform.setOrigin(Bullet::v3ToBullet(getTorso()->getPosition()));
            ghostTransform.setRotation(Bullet::qtToBullet(getTorso()->getRotation()));
            m_playerGhostObject->setWorldTransform(ghostTransform);

            world->getDynamicsWorld()->addCollisionObject(m_playerGhostObject, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
            world->getDynamicsWorld()->addAction(m_characterController);
        }
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
        PartInstance* torso = getTorso();
        Camera* camera = world->getWorkspace()->getCurrentCamera();
        if(!torso)
        {
            printf("Humanoid::inputFrame: no torso\n");
            return;
        }
        if(inputManager)
        {
            Ogre::Matrix3 camera_rotation;
            camera_rotation.FromEulerAnglesYXZ(camera->getYaw(), Ogre::Radian(0), Ogre::Radian(0)); // we only want yaw because otherwise the movement target will go through the ground/in the air
            Ogre::Quaternion direction = torso->getRotation();
            Ogre::Quaternion new_direction = Ogre::Quaternion::nlerp(0.5f, direction, camera_rotation);
            float forward = 0;

            if(inputManager->isKeyDown('W'))
                forward = 16;

            Ogre::Vector3 move = Ogre::Vector3(0, 0, forward);
            move = direction * move;
            move *= world->getComPlicitNgine()->getLastPhysicsDelta();

            bool move_valid = true;

            // TODO: collision checking

            if(!move_valid)
                return;

            for(auto& child : *getParent()->getChildren())
            {
                PartInstance* bp = dynamic_cast<PartInstance*>(child);
                if(bp)
                {
                    Ogre::Vector3 bp_p = bp->getRelativePosition(getTorso());

                    bp->getCFrame().setPosition(bp_p + Bullet::v3ToOgre(m_characterController->getGhostObject()->getWorldTransform().getOrigin()));
                    Ogre::Matrix3 new_rotation_matrix;
                    new_direction.ToRotationMatrix(new_rotation_matrix);
                    bp->getCFrame().setRotation(new_rotation_matrix);
                    bp->updateMatrix();
                    world->getComPlicitNgine()->updatePhysicsPart(bp);
                    world->getWorkspace()->setDirty();
                }
            }

            camera->getCFrame().setPosition(camera->getCFrame().getPosition() + move);
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
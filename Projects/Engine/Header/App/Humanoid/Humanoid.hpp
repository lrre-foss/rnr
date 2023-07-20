#pragma once

#include <App/V8/Tree/Instance.hpp>
#include <App/V8/DataModel/PartInstance.hpp>

namespace RNR
{
    class Humanoid : public Instance
    {
        public:
            Humanoid();
            ~Humanoid();

            virtual std::string getClassName() { return "Humanoid"; }
        
            bool canSit();
            void buildJoints();
            void checkForJointDeath();
            void computeForce(float force, bool throttling);
            PartInstance* getTorso();
            PartInstance* getHead(); 
            
            void inputFrame(float dx, float dy);
            void createHealthBar();

            float getHealth() { return m_health; };
            void setHealth(float health) { m_health = health; }
            float getMaxHealth() { return m_maxHealth; }
            void setMaxHealth(float maxHealth) { m_maxHealth = maxHealth; }
        private:
            virtual void deserializeProperty(char* prop_name, pugi::xml_node prop);
            virtual void addProperties(std::vector<ReflectionProperty>& properties);
            float m_health;
            float m_maxHealth;
            float m_walkRotationalVelocity;
    };
}
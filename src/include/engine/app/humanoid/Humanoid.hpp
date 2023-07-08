#pragma once

#include <engine/app/v8/tree/Instance.hpp>

namespace RNR
{
    class Humanoid : Instance
    {
        private:
            float m_health;
            float m_maxHealth;
            float m_walkRotationalVelocity;
        public:
            Humanoid();
            ~Humanoid();
        
            bool canSit();
            void buildJoints();
            void checkForJointDeath();
            void computeForce(float force, bool something);
            void getTorso();
            void getHead();
    };
}
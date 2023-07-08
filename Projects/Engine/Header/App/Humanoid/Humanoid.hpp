#pragma once

#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    class Humanoid : Instance
    {
        public:
            Humanoid();
            ~Humanoid();
        
            bool canSit();
            void buildJoints();
            void checkForJointDeath();
            void computeForce(float force, bool throttling);
            void getTorso();
            void getHead();
        
        private:
            float m_health;
            float m_maxHealth;
            float m_walkRotationalVelocity;
    };
}
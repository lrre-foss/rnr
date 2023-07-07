#ifndef __APP_HUMANOID_HUMANOID_HPP__
#define __APP_HUMANOID_HUMANOID_HPP__
#include <engine/app/v8/tree/Instance.hpp>

namespace RBX
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

#endif  
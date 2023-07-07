#pragma once

namespace RBX
{
    class World
    {
        public:
            World();
            ~World();

            void preStep();
            double step(float timestep);
            void update();
    };
}
#pragma once

namespace RNR
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
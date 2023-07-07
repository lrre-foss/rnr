#ifndef __APP_V8_WORLD_WORLD_HPP__
#define __APP_V8_WORLD_WORLD_HPP__

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

#endif
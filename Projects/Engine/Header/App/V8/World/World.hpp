#pragma once

#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    class World
    {
        private:
            Instance* m_datamodel;

        public:
            World();
            ~World();

            void preStep();
            double step(float timestep);
            void update();

            Instance* getDatamodel() { return m_datamodel; }
            void setDatamodel(Instance* instance) { m_datamodel = instance; }
    };
}
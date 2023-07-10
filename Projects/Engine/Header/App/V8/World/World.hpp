#pragma once

#include <App/V8/Tree/Instance.hpp>
#include <App/V8/World/Workspace.hpp>

namespace RNR
{
    class World
    {
        private:
            Instance* m_datamodel;
            Workspace* m_workspace;

        public:
            World();
            ~World();

            void preStep();
            double step(float timestep);
            void update();

            Instance* getDatamodel() { return m_datamodel; }
            void setDatamodel(Instance* instance) { m_datamodel = instance; }
            Workspace* getWorkspace() { return m_workspace; }
            void setWorkspace(Workspace* workspace) { m_workspace = workspace; }
    };
}
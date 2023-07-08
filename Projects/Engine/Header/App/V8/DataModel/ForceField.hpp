#pragma once

#include <Rendering/Adorn.hpp>

namespace RNR
{
    class ForceField
    {
        public:
            ForceField();
            ~ForceField();

            void renderForceField(boost::shared_ptr<RNR::Instance>* descendant, RNR::Adorn* adorn, int cycle);
    }
}
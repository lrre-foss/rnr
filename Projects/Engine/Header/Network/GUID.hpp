#pragma once

#include <string>

#include <App/Helpers/Strings.hpp>

namespace RNR
{
    class GUID
    {
        public:
            GUID();

            std::string generateGUID();
            static void compare(RNR::GUID* a, RNR::GUID* b);
    };
}
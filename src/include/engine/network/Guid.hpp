#pragma once

#include <string>

namespace RNR
{
    class Guid
    {
    public:
        Guid();

        static void generateGUID(std::string *result);
        static void compare(RNR::Guid* a, RNR::Guid* b);
    };
}
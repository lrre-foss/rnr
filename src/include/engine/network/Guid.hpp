#pragma once

#include <string>

namespace RBX
{
    class Guid
    {
    public:
        Guid();

        static void generateGUID(std::string *result);
        static void compare(RBX::Guid* a, RBX::Guid* b);
    };
}
#ifndef __NETWORK_GUID_HPP__
#define __NETWORK_GUID_HPP__

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

#endif
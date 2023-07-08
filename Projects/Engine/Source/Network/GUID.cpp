#include <Network/Guid.hpp>

namespace RNR
{
    Guid::Guid()
    {

    }

    void Guid::compare(Guid* a, Guid* b)
    {

    }

    std::string Guid::generateGUID()
    {
        return "RBX" + Strings::generateRandomString(16);
    }
}
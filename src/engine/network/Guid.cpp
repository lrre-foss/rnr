#include <engine/network/Guid.hpp>

RBX::Guid::Guid()
{

}

void RBX::Guid::compare(RBX::Guid* a, RBX::Guid* b)
{

}

void RBX::Guid::generateGUID(std::string* result)
{
#ifdef _WIN32
    GUID pguid;
    wchar_t sz[64];
    char MultiByteStr[64];
    CoCreateGuid(&pguid);
    memset(sz, 0, sizeof(sz));
    StringFromGUID2(&pguid)
    WideCharToMultiByte(0, 0, sz, 64, MultiByteStr, 64, 0, 0);
    result += MultiByteStr;
#else 
    // TBD: POSIX method
#endif
}
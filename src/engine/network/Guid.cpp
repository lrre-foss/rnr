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

    // construct guid
    result = "RBX";
    result += MultiByteStr;
    result->erase(40, 1);
    result->erase(27, 1);
    result->erase(22, 1);
    result->erase(17, 1);
    result->erase(3, 1);
#else 
    // TBD: POSIX method
#endif
}
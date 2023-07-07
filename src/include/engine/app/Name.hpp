#ifndef __APP_NAME_HPP__
#define __APP_NAME_HPP__

#include <map>

namespace RBX
{
    class Name
    {
    public:

        char* c_str();

        static void compare(const RBX::Name *a, const RBX::Name *b);
        static void declare(const char* sName, int dictionaryIndex);
        static std::map<int, RBX::Name*>* dictionary();
    };
}

#endif
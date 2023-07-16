#pragma once 

#include <string>
#include <boost/type_index.hpp>

namespace RNR
{
    enum ReflectionPropertyAccess
    {
        ACCESS_SCRIPT,
        ACCESS_CONSOLE,
        ACCESS_RNR,
    };

    template <class T>
    class ReflectionProperty
    {
    private:
        std::string m_name;
        ReflectionPropertyAccess m_access;
    public:
        ReflectionProperty(std::string name, ReflectionPropertyAccess access, T(*getter), T(*setter))
        {
            this->m_name = name;
            this->m_access = access;
            this->getter = getter;
            this->setter = setter;
        }

        bool access(ReflectionPropertyAccess accessor)
        {
            return this->m_access <= accessor;
        }

        char* class_name()
        {
            return boost::typeindex::type_id<T>().pretty_name();
        }

        T (*getter)();
        void (*setter)(T val);
    };
}
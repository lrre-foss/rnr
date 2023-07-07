#ifndef __APP_V8_TREE_INSTANCE_HPP__
#define __APP_V8_TREE_INSTANCE_HPP__

#include <string>

namespace RBX
{
    class Instance
    {
        private:
            std::string m_name;
        public:
            Instance();
            void setName(std::string name);

    }
}

#endif
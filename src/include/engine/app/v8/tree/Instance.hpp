#ifndef __APP_V8_TREE_INSTANCE_HPP__
#define __APP_V8_TREE_INSTANCE_HPP__

#include <string>
#include <engine/app/Name.hpp>
#include <boost/shared_ptr.hpp>

namespace RBX
{
    class Instance
    {
        private:
            std::string m_name;
            RBX::Instance* m_parent;
            std::vector<boost::shared_ptr<RBX::Instance>> m_children;
            bool m_archivable;
        public:
            Instance();
            Instance(char* name);

            bool contains(RBX::Instance* child);
            bool isAncestorOf(RBX::Instance* instance);

            virtual bool askSetParent(RBX::Instance* instance); // derive this
            bool canSetParent(RBX::Instance* instance);
            virtual bool askAddChild(RBX::Instance* instance); // derive this
            bool canAddChild(RBX::Instance* instance);

            void createChild(boost::shared_ptr<RBX::Instance>* result, const RBX::Name *className);
            
            RBX::Instance* getParent() { return this->m_parent; };
            std::string getName() { return this->m_name };

            void setParent(RBX::Instance* newParent);
            void setName(std::string name);
            std::vector<boost::shared_ptr<RBX::Instance>>* getChildren() { return &this->m_children; };
            int numChildren() { return this->m_children.size() };

            void onChildAdded(RBX::Instance* childAdded);

    };
}

#endif
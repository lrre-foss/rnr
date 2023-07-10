#pragma once

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Helpers/Name.hpp>

namespace RNR
{
    class Instance
    {
        private:
            std::string m_name;
            RNR::Instance* m_parent;
            std::vector<RNR::Instance*> m_children;
            bool m_archivable;
        
        public:
            Instance();
            Instance(std::string name);
            ~Instance();
            
            bool contains(RNR::Instance* child);
            bool isAncestorOf(RNR::Instance* instance);

            virtual bool askSetParent(RNR::Instance* instance); // derive this
            bool canSetParent(RNR::Instance* instance);
            virtual bool askAddChild(RNR::Instance* instance); // derive this
            bool canAddChild(RNR::Instance* instance);

            RNR::Instance* createChild(const RNR::Name *className);
            
            RNR::Instance* getParent() { return this->m_parent; };
            std::string getName() { return this->m_name; };

            void setParent(RNR::Instance* newParent);
            void setName(std::string name);
            std::vector<RNR::Instance*>* getChildren() { return &this->m_children; };
            int numChildren() { return this->m_children.size(); };

            void onChildAdded(RNR::Instance* childAdded);
    };
}
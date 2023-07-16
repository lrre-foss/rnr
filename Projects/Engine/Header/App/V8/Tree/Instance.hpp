#pragma once

#include <stdexcept>
#include <string>

#include <OGRE/Ogre.h>
#include <boost/shared_ptr.hpp>

#include <Helpers/Name.hpp>
#include <pugixml.hpp>

namespace RNR
{
    class World;

    class Instance
    {
        protected:
            static World* world;
            virtual void deserializeProperty(char* prop_name, pugi::xml_node prop) {};

        private:

            Ogre::SceneNode* m_node;
            Ogre::MovableObject* m_object;
            std::string m_name;
            RNR::Instance* m_parent;
            std::vector<RNR::Instance*> m_children;
            bool m_archivable;
        
        public:
            Instance();
            ~Instance();
            
            void deserializeXmlProperty(pugi::xml_node prop);

            bool contains(RNR::Instance* child);
            bool isAncestorOf(RNR::Instance* instance);

            static void setWorld(World* world) { Instance::world = world; }

            virtual bool askSetParent(RNR::Instance* instance); // derive this
            bool canSetParent(RNR::Instance* instance);
            virtual bool askAddChild(RNR::Instance* instance); // derive this
            bool canAddChild(RNR::Instance* instance);

            RNR::Instance* createChild(const RNR::Name *className);
            
            RNR::Instance* getParent() { return this->m_parent; };
            std::string getName() { return this->m_name; };
            virtual std::string getClassName() { return "Instance"; }

            void setParent(RNR::Instance* newParent);
            void setName(std::string name);
            void setNode(Ogre::SceneNode* node) { m_node = node; };
            Ogre::SceneNode* getNode() { return m_node; };
            void setObject(Ogre::MovableObject* object) { m_object = object; };
            Ogre::MovableObject* getObject() { return m_object; };
            std::vector<RNR::Instance*>* getChildren() { return &this->m_children; };
            int numChildren() { return this->m_children.size(); };

            virtual void onChildAdded(RNR::Instance* childAdded);
            virtual void onChildRemoved(RNR::Instance* childRemoved);
    };
}
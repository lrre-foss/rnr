#include <App/V8/DataModel/DataModel.hpp>
#include <App/V8/Tree/InstanceFactory.hpp>
#include <App/Script/Script.hpp>
#include <Helpers/Strings.hpp>

namespace RNR
{
    const char* DATAMODEL_NO_GUID = "?";

    DataModel::DataModel()
    {

    }

    Instance* DataModel::getService(std::string service_name)
    {
        Instance* service = findFirstChildOfType(service_name);
        if(!service)
            service = findFirstChild(service_name);
        if(!service)
        {
            try{
                service = InstanceFactory::singleton()->build(service_name);
                if(service)
                {
                    service->setParent(this);
                }
            }
            catch(std::runtime_error e)
            {
                printf("DataModel::getService: InstanceFactory::build failed  '%s'\n", e.what());
            }
        }
        return service;
    }

    void DataModel::addFunctions(std::vector<ReflectionFunction>& functions)
    {
        functions.push_back({"GetService",[](lua_State* l){DataModel* instance = (DataModel*)QUICK_GET_INSTANCE(l, 1); Lua::InstanceBridge::singleton()->fromInstance(l, instance->getService(lua_tostring(l, 2))); return 1; }});
    }

    Instance* DataModel::getInstanceByGuid(std::string guid)
    {
        auto it = m_guids.find(guid);
        if(it != m_guids.end())
            return it->second;
        printf("DataModel::getInstanceByGuid: unknown guid '%s'\n", guid.c_str());
        return NULL;
    }

    void DataModel::removeInstanceByGuid(std::string guid)
    {
        auto it = m_guids.find(guid);
        if(it != m_guids.end())
            m_guids.erase(it);
    }

    void DataModel::registerInstanceByGuid(Instance* instance, std::string guid)
    {
        printf("DataModel::registerInstanceByGrid: %s -> %s\n", instance->getName().c_str(), guid.c_str());
        m_guids[guid] = instance;
    }

    std::string DataModel::getGuidByInstance(Instance* instance)
    {
        for(auto it : m_guids)
        {
            if(it.second == instance)
                return it.first;
        }
        
        std::string new_guid = Strings::random_hex(8); // gen a new one
        m_guids[new_guid] = instance;
        printf("DataModel::getGuidByInstance: unregistered instance %s (%s, new guid for this is %s)\n", instance->getName().c_str(), instance->getClassName().c_str(), new_guid.c_str());
        return new_guid;
    }

    void DataModel::onDescendantAdded(Instance* childAdded)
    {
        if(getGuidByInstance(childAdded) == DATAMODEL_NO_GUID)
        {
            std::string guid = Strings::random_hex(8);
            registerInstanceByGuid(childAdded, guid);
        }
    }

    void DataModel::onDescendantRemoved(Instance* childRemoved)
    {
        std::string guid = getGuidByInstance(childRemoved);
        if(guid != DATAMODEL_NO_GUID)
            removeInstanceByGuid(guid);
    }
} 

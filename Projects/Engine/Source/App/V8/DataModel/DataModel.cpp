#include <App/V8/DataModel/DataModel.hpp>
#include <App/V8/Tree/InstanceFactory.hpp>

namespace RNR
{
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
} 

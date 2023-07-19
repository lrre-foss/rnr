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
        {
            service = InstanceFactory::singleton()->build(service_name);
            if(service)
            {
                service->setParent(this);
            }
        }
        return service;
    }
} 

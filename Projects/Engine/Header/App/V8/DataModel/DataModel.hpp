#pragma once
#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    class DataModel : public Instance
    {
    public:
        DataModel();

        Instance* getService(std::string service_name);
    private:

    };
}
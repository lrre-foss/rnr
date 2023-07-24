#include <Network/NetworkPeer.hpp>

namespace RNR
{
    class NetworkClient : public NetworkPeer
    {
    public:
        NetworkClient();
                
        virtual std::string getClassName() { return "NetworkClient"; }
    };
}
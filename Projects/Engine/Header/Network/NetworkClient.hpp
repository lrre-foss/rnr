#include <Network/NetworkPeer.hpp>

namespace RNR
{
    class NetworkClient : public NetworkPeer
    {
    public:
        NetworkClient();

        void connect(char* ip, int port);
        void frame();
                
        virtual std::string getClassName() { return "NetworkClient"; }
    };
}
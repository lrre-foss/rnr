#pragma once
#include <Network/ArkNet/ArkPeer.hpp>
#include <Network/ArkNet/ArkServer.hpp>
#include <Network/NetworkPeer.hpp>
#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    class NetworkServer : public NetworkPeer
    {
    protected:
        ArkNet::ArkServer* m_server;
        int m_port;
    public:
        NetworkServer();
        ~NetworkServer();

        void start(int port, int threadSleepTime);
        void stop(int blockDuration);

        virtual std::string getClassName() { return "NetworkServer"; }
    };
}
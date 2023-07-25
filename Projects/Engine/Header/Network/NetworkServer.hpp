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
        bool m_running;
    public:
        NetworkServer();
        ~NetworkServer();

        void start(int port, int threadSleepTime = 20);
        void stop(int blockDuration = 1000);
        void frame();

        bool getRunning() { return m_running; }
        virtual std::string getClassName() { return "NetworkServer"; }
    };
}
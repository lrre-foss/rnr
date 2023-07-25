#include <Network/NetworkServer.hpp>

namespace RNR
{
    NetworkServer::NetworkServer() : NetworkPeer()
    {
        m_server = new ArkNet::ArkServer(m_peer);
        m_running = false;
    }

    void NetworkServer::start(int port, int threadTime)
    {
        // TODO: create network thread that times out
        // every frame it should sleep for (threadTime/1000.0)-delta time

        m_socket->bindServer("0.0.0.0", port);
        printf("NetworkServer::start: network server running on port %i\n", port);
        m_running = true;
    }

    void NetworkServer::frame()
    {
        if(m_running)
            m_server->frame();
    }

    void NetworkServer::stop(int timeout)
    {
        m_socket->closeSocket();
        m_running = false;
    }
}
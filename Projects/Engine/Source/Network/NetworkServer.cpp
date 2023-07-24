#include <Network/NetworkServer.hpp>

namespace RNR
{
    NetworkServer::NetworkServer() : NetworkPeer()
    {
        m_server = new ArkNet::ArkServer(m_peer);
    }

    void NetworkServer::start(int port, int threadTime)
    {
        // TODO: create network thread that times out
        // every frame it should sleep for (threadTime/1000.0)-delta time

        m_socket->bindServer("0.0.0.0", port);
        printf("NetworkServer::start: network server running on port %i\n", port);
    }

    void NetworkServer::stop(int timeout)
    {
        m_socket->closeSocket();
    }
}
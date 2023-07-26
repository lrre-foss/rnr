#include <Network/NetworkServer.hpp>
#include <Network/NetworkReplicator.hpp>

namespace RNR
{
    NetworkServer::NetworkServer() : NetworkPeer()
    {
        setName("NetworkServer");
        m_server = new ArkNet::ArkServer(m_peer);
        m_server->setListener(this);
        m_running = false;
    }

    NetworkServer::~NetworkServer()
    {
        stop();
    }

    void NetworkServer::onPeerAdding(ArkNet::ArkPeer* addingPeer)
    {
        NetworkReplicator* peer_replicator = new NetworkReplicator(addingPeer);
        peer_replicator->setParent(this);
    }

    void NetworkServer::onPeerRemoving(ArkNet::ArkPeer* removingPeer)
    {
        for(auto& child : *getChildren())
        {
            NetworkReplicator* replicator = dynamic_cast<NetworkReplicator*>(child);
            if(replicator)
            {
                replicator->setParent(NULL);
                delete replicator;
            }
        }
    }

    void NetworkServer::start(int port, int threadTime)
    {
        // TODO: create network thread that times out
        // every frame it should sleep for (threadTime/1000.0)-delta time

        m_socket->bindServer("127.0.0.1", port);
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
#include <Network/NetworkClient.hpp>
#include <Network/NetworkReplicator.hpp>

namespace RNR
{
    NetworkClient::NetworkClient()
    {
        setName("NetworkClient");
        m_peer->addListener(this);
    }

    void NetworkClient::connect(char *ip, int port)
    {
        m_socket->tryConnect(ip, port);

        NetworkReplicator *replicator = new NetworkReplicator(m_peer);
        replicator->setParent(this);
    }

    void NetworkClient::disconnect()
    {
        
    }

    void NetworkClient::frame()
    {
        m_peer->clientPump();
        sendPendingReplicates();
    }

    void NetworkClient::onPacketReceiving(ArkNet::ArkPeer *peer, ArkNet::ArkPacket *packet)
    {
    }
}
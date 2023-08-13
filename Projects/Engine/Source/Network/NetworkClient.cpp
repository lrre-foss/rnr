#include <Network/NetworkClient.hpp>
#include <Network/NetworkReplicator.hpp>
#include <Network/ArkNet/Packets.hpp>

namespace RNR
{
    NetworkClient::NetworkClient()
    {
        setName("NetworkClient");
        m_peer->addListener(this);
    }

    void NetworkClient::connect(char* ip, int port)
    {
        m_socket->tryConnect(ip, port);

        ArkNet::Packets::OpenConnectionRequestPacket request;
        request.playerName = "Player";
        m_peer->sendPacket(&request);

        NetworkReplicator* replicator = new NetworkReplicator(m_peer);
        replicator->setParent(this);
    }

    void NetworkClient::frame()
    {
        m_peer->clientPump();
    }

    void NetworkClient::onPacketReceiving(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet)
    {
        
    } 
}
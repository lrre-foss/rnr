#include <Network/NetworkClient.hpp>
#include <Network/ArkNet/Packets.hpp>

namespace RNR
{
    NetworkClient::NetworkClient()
    {
        setName("NetworkClient");
    }

    void NetworkClient::connect(char* ip, int port)
    {
        m_socket->tryConnect(ip, port);

        ArkNet::Packets::OpenConnectionRequestPacket request;
        request.playerName = "Player";
        m_peer->sendPacket(&request);
    }

    void NetworkClient::frame()
    {
        
    }
}
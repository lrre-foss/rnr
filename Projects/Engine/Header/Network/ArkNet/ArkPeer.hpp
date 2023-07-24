#pragma once
#include <Network/ArkNet/ArkSocket.hpp>
#include <Network/ArkNet/ArkAddress.hpp>
#include <Network/ArkNet/ArkPacket.hpp>

namespace ArkNet
{
    class ArkPeer
    {
    private:
        ArkAddress m_remote;
        ArkSocket* m_socket;
    public:
        ArkPeer(ArkSocket* socket);
        ArkPeer(ArkAddress remote, ArkSocket* socket);
        ~ArkPeer();

        void setRemote(ArkAddress remote) { m_remote = remote; };

        int recvFrom(int bytes, char* data, ArkAddress* remote, int flags = 0);
        int sendTo(int bytes, char* data, int flags = 0);
        ArkPacket* recvPacket(ArkAddress* remote);
        void sendPacket(ArkPacket* packet);

        ArkSocket* getSocket() { return m_socket; }
    };
}
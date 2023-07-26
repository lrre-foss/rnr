#pragma once
#include <Network/ArkNet/ArkSocket.hpp>
#include <Network/ArkNet/ArkAddress.hpp>
#include <Network/ArkNet/ArkPacket.hpp>
#include <Network/ArkNet/ArkUserData.hpp>
#include <vector>

namespace ArkNet
{
    class ArkPeer;
    class IArkPeerListener
    {
    public:
        virtual void onPacketReceiving(ArkPeer* peer, ArkPacket* packet) = 0;
    };

    class ArkPeer
    {
    private:
        friend class ArkServer;
        ArkAddress m_remote;
        ArkSocket* m_socket;
        ArkUserData* m_userData;
        std::vector<IArkPeerListener*> m_listeners;
    public:
        ArkPeer(ArkSocket* socket);
        ArkPeer(ArkAddress remote, ArkSocket* socket);
        ~ArkPeer();

        void setRemote(ArkAddress remote) { m_remote = remote; };
        void addListener(IArkPeerListener* listener) { m_listeners.push_back(listener); }

        int recvFrom(int bytes, char* data, ArkAddress* remote, int flags = 0);
        int sendTo(int bytes, char* data, int flags = 0);
        ArkPacket* recvPacket(ArkAddress* remote);
        void sendPacket(ArkPacket* packet);

        ArkSocket* getSocket() { return m_socket; }
        ArkUserData* getUserData() { return m_userData; }
    };
}
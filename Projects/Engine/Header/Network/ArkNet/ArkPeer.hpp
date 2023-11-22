#pragma once
#include <Network/ArkNet/ArkSocket.hpp>
#include <Network/ArkNet/ArkAddress.hpp>
#include <Network/ArkNet/ArkPacket.hpp>
#include <Network/ArkNet/ArkUserData.hpp>
#include <vector>
#include <list>
#include <map>
#include <deque>

namespace ArkNet
{
    class ArkPeer;
    class IArkPeerListener
    {
    public:
        // for raw packets, basically anything that isnt intercepted by ArkPeer
        virtual void onPacketReceiving(ArkPeer* peer, ArkPacket* packet) {};
        // for game packets sent via sendReliablePacket, this is probably the one you want to override
        virtual void onGamePacketReceiving(ArkPeer* peer, ArkPacket* packet) {}; // packets with security

        virtual void onConnectionAccepted(ArkPeer* peer) {};
        virtual void onDisconnected(ArkPeer* peer) {};
    };

    struct PendingPacket
    {
        unsigned char* data;
        int dataSz;
        int sendAtFrame;
        int fspIndex;
        int flags;
    };

    struct MegaPacket
    {
        ArkPacket* packet;
        int size;
        int packetsToBeReceived;
        int packetsReceived;
    };

    class ArkPeer
    {
    private:
        friend class ArkServer;
        ArkAddress m_remote;
        ArkSocket* m_socket;
        ArkUserData* m_userData;
        std::deque<PendingPacket> m_pendingPackets;
        std::vector<IArkPeerListener*> m_listeners;
        int m_lastSentFspIndex;
        int m_lastRecvFspIndex;
        int m_lastFragmentId;
        std::map<int, MegaPacket> m_incomingMegaPackets;
        bool m_authorized;
        int m_peerFrame;
        int m_nextConnectionAttempt;
        int m_connectionAttempts;
        int m_connectionStage;
        int m_peerMTU;
    public:
        ArkPeer(ArkSocket* socket);
        ArkPeer(ArkAddress remote, ArkSocket* socket);
        ~ArkPeer();

        void disconnect(std::string reason, bool silent = false); // set silent to true if the client is responding to a server disconnect

        void setRemote(ArkAddress remote) { m_remote = remote; };
        void addListener(IArkPeerListener* listener) { m_listeners.push_back(listener); }

        int recvFrom(int bytes, unsigned char* data, ArkAddress* remote, int flags = 0);
        int sendTo(int bytes, unsigned char* data, int flags = 0);
        ArkPacket* recvPacket(ArkAddress* remote);
        // most likely you want to be using sendReliablePacket, as this provides no reliability
        // or fragmenting or ordering or sequencing or anything that you want
        // the first byte of a packet sent using sendPacket is the ArkNet packet type
        // and should be something that isnt already used (look at ArkPeer::pumpReadPacket)
        void sendPacket(ArkPacket* packet);
        // sendReliablePacket requires ArkPeer::frame to be called continually,
        // clientPump automatically handles calling it if you use it
        // reliable packets will also not signal onPacketReceiving, and instead use onGamePacketReceiving
        void sendReliablePacket(ArkPacket* packet, PacketReliablity reliablity);

        void authorize();

        int newFspIndex() { return m_lastSentFspIndex++; }
        int getConnectionAttempts() { return m_connectionAttempts; }
        int getConnectionStage() { return m_connectionStage; }
        
        void sendAcknowledge(int record);

        bool pumpReadPacket(ArkPacket* in_packet);
        // read events, client-only, servers should use ArkServer::frame
        void clientPump(); 
        void frame();

        ArkSocket* getSocket() { return m_socket; }
        ArkUserData* getUserData() { return m_userData; }
        int getMTU() { return m_peerMTU; }
        // this should be used for sendReliablePacket packets, as sending a reliable packet will add an extra overhead to it
        int getGamePacketMTU() { return m_peerMTU - 64; } // TODO: make this better
    };
}
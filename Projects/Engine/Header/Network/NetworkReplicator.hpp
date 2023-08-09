#pragma once
#include <Network/ArkNet/ArkPeer.hpp>
#include <Network/Player.hpp>
#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    class NetworkReplicator : public Instance, public ArkNet::IArkPeerListener
    {
        ArkNet::ArkPeer* m_peer;
        Player* m_player;
    public:
        NetworkReplicator(ArkNet::ArkPeer* peer);
        ~NetworkReplicator();

        void sendInstance(Instance* instance);
        void sendReflectionProperty(ReflectionProperty prop);
        void sendInstanceProps(Instance* instance);
        void sendDelInstance(Instance* instance);

        void sendMarker();
        ArkNet::ArkPeer* getPeer() { return m_peer; };
        Player* getPlayer() { return m_player; }
        void setPlayer(Player* player) { m_player = player; }
        virtual void onPacketReceiving(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet);        
        virtual std::string getClassName() { return "NetworkReplicator"; }
    };
}
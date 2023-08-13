#pragma once
#include <Network/ArkNet/ArkPeer.hpp>
#include <Network/Player.hpp>
#include <Network/Marker.hpp>
#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    struct MarkerItem;

    class NetworkReplicator : public Instance, public ArkNet::IArkPeerListener
    {
        std::vector<Network::Marker*> m_incomingMarkers;
        std::vector<int> m_pendingMarkers;
        ArkNet::ArkPeer* m_peer;
        Player* m_player;

        bool m_serverReplicator; // if this NetworkReplicator is from a NetworkServer
    public:
        NetworkReplicator(ArkNet::ArkPeer* peer, bool serverReplicator = false);
        ~NetworkReplicator();

        void readDataPacket(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet);

        void sendInstance(Instance* instance);
        void sendReflectionProperty(ReflectionProperty prop);
        void sendInstanceProps(Instance* instance);
        void sendDelInstance(Instance* instance);

        Network::Marker* sendMarker();
        void processMarker(int id);

        ArkNet::ArkPeer* getPeer() { return m_peer; };
        Player* getPlayer() { return m_player; }
        void setPlayer(Player* player) { m_player = player; }
        virtual void onPacketReceiving(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet);        
        virtual std::string getClassName() { return "NetworkReplicator"; }
    };
}
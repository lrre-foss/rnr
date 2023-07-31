#pragma once
#include <Network/ArkNet/ArkPeer.hpp>
#include <App/V8/Tree/Instance.hpp>

namespace RNR
{
    class NetworkReplicator : public Instance, public ArkNet::IArkPeerListener
    {
        ArkNet::ArkPeer* m_peer;
    public:
        NetworkReplicator(ArkNet::ArkPeer* peer);
        ~NetworkReplicator();

        virtual void onPacketReceiving(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet);        
        virtual std::string getClassName() { return "NetworkReplicator"; }
    };
}
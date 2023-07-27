#pragma once
#include <Network/NetworkReplicator.hpp>
#include <Network/NetworkServer.hpp>
#include <Network/NetworkClient.hpp>

namespace RNR
{
    NetworkReplicator::NetworkReplicator(ArkNet::ArkPeer* peer) : Instance()
    {
        setName("NetworkReplicator");
        m_peer = peer;
        m_peer->addListener(this);
    }

    NetworkReplicator::~NetworkReplicator()
    {
        // TODO: remove listener (should be done asap actually)
    }

    void NetworkReplicator::onPacketReceiving(ArkNet::ArkPeer* peer, ArkNet::ArkPacket* packet)
    {
        
    } 
}
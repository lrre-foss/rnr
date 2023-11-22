#include <Network/ArkNet/ArkServer.hpp>

namespace ArkNet
{
    ArkServer::ArkServer(ArkPeer *server)
    {
        m_peer = server;
        m_serverListener = 0;

        if (server)
            server->addListener(this);
    }

    void ArkServer::frame()
    {
        if (m_peer->getSocket()->getSocketStatus() == ARKSOCKET_CONNECTED)
        {
            char data_id;
            ArkAddress remote_addr = ArkAddress();
            ArkPacket *in_packet = m_peer->recvPacket(&remote_addr);
            if (in_packet)
            {
                auto peer_it = m_peers.find(remote_addr.toString());
                ArkPeer *peer;
                if (peer_it == m_peers.end())
                {
                    peer = new ArkPeer(remote_addr, m_peer->getSocket());
                    printf("ArkServer::frame: new ArkPeer %s incoming\n", remote_addr.toString().c_str());
                    m_peers[remote_addr.toString()] = peer;
                }
                else
                    peer = m_peers[remote_addr.toString()];

                if(!peer->pumpReadPacket(in_packet))
                {
                    for (auto &listener : m_peer->m_listeners)
                        listener->onPacketReceiving(peer, in_packet);
                    for (auto &listener : peer->m_listeners)
                        listener->onPacketReceiving(peer, in_packet);
                }
                delete in_packet;
            }
            
            for(auto peer : m_peers)
                peer.second->frame();
            m_peer->frame();
        }
    }

    void ArkServer::onPacketReceiving(ArkPeer *peer, ArkPacket *packet)
    {
        ArkStream dataStream(packet->data, packet->dataSz);
        ArkPacket psub = packet->sub(1, packet->dataSz - 1);
        switch (dataStream.read<unsigned char>())
        {
        case 0x05: // connection request 1
        {
            printf("ArkServer::onPacketReceiving: received a connection request\n");
            bool accept = true;
            if (!dataStream.readMagic())
            {
                printf("ArkServer::onPacketReceiving: received bad magic from peer\n");
            }
            peer->m_peerMTU = packet->dataSz;
            printf("ArkServer::onPacketReceiving: new clients MTU is %i\n", peer->m_peerMTU);
            ArkPacket connReply(32);
            ArkStream connStream(&connReply);
            connStream.write<char>(0x06);
            connStream.write<unsigned short>(peer->getMTU());
            peer->sendPacket(&connReply);
        }
            break;
        case 0x07: // connection request 2
        {
            bool accept = true;
            printf("ArkServer::onPacketReceiving: received a connection request 2\n");
            if (m_serverListener)
                accept = m_serverListener->onPeerConnectionRequest(peer, &psub);
            if(accept)
            {
                if (m_serverListener)
                    m_serverListener->onPeerAdding(peer);
                peer->authorize();
                ArkPacket connReply(32);
                ArkStream connStream(&connReply);
                connStream.write<char>(0x08);
                peer->sendPacket(&connReply);
            }
        }
            break;
        default:
            break;
        }
    }
}
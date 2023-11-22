#include <Network/ArkNet/ArkPeer.hpp>
#include <stdexcept>
#include <algorithm>
#include <math.h>

namespace ArkNet
{
    ArkPeer::ArkPeer(ArkSocket *socket)
    {
        m_socket = socket;

        m_lastRecvFspIndex = 0;
        m_lastSentFspIndex = 0;
        m_nextConnectionAttempt = 0;
        m_connectionAttempts = 0;
        m_connectionStage = 0;
        m_lastFragmentId = 0;
        m_peerFrame = 0;
        m_peerMTU = 65507; // max UDP payload over IPv4, ArkNet will get the MTU by continually
                           // requesting the server
    }

    ArkPeer::ArkPeer(ArkAddress remote, ArkSocket *socket)
    {
        m_remote = remote;
        m_socket = socket;
    }

    ArkPeer::~ArkPeer()
    {
    }

    int ArkPeer::recvFrom(int bytes, unsigned char *data, ArkAddress *remote, int flags)
    {
        return m_socket->recvFrom(remote, bytes, data, flags);
    }

    int ArkPeer::sendTo(int bytes, unsigned char *data, int flags)
    {
        return m_socket->sendTo(&m_remote, bytes, data, flags);
    }

    void ArkPeer::authorize()
    {
        printf("ArkPeer::authorize: authorized %s\n", m_remote.toString().c_str());
        m_authorized = true;
    }

    ArkPacket *ArkPeer::recvPacket(ArkAddress *remote)
    {
        unsigned char packet_buf[65535];
        try
        {
            int sz = recvFrom(65535, packet_buf, remote, 0);
            if (sz == -1)
                return NULL;
            ArkPacket *packet = new ArkPacket();
            packet->data = new unsigned char[sz];
            packet->dataSz = sz;
            memcpy(packet->data, packet_buf, packet->dataSz);
            return packet;
        }
        catch (std::runtime_error e)
        {
            printf("ArkPeer::recvPacket: error on receive (what:%s)\n", e.what());
        }
        return NULL;
    }

    void ArkPeer::sendPacket(ArkPacket *packet)
    {
        sendTo(packet->dataSz, packet->data, 0);
    }

    void ArkPeer::sendReliablePacket(ArkPacket *packet, PacketReliablity reliablity)
    {
        ArkPacket bpacket = ArkPacket(packet->dataSz + 64);
        ArkStream inpackets = ArkStream(packet);
        ArkStream bpackets = ArkStream(&bpacket);

        FrameSetPacket fsp;
        fsp.frameSetIndex = newFspIndex();
        fsp.bitLength = packet->dataSz * 8;
        fsp.flags = 0;
        fsp.frameSequenceIndex = 0;
        fsp.frameSequenceIndex = 0;
        fsp.orderedChannel = 0;
        fsp.orderedFrameIndex = 0;
        fsp.fragmentCompoundID = 0;
        fsp.fragmentCompoundSize = 0;
        fsp.fragmentIndex = 0;
        bool actuallySend = true;
        bool pendPacket = false;
        bool sequenced = false;
        bool ordered = false;
        bool ack = false;

        // kinda sucks that i have to use gotos but it is what it is
        switch(reliablity)
        {
        case UNRELIABLE_ACK:
            ack = true;
            goto unreliable_packet_label;
        case RELIABLE_ACK:
            ack = true;
            goto reliable_packet_label;
        case RELIABLE_ORD_ACK:
            ack = true;
            goto reliable_ord_packet_label;
        case UNRELIABLE_SEQ:
            sequenced = true;
        case UNRELIABLE: // why even send unreliable packets through sendReliablePacket
        unreliable_packet_label:
            break;       // do nothing
        case RELIABLE_SEQ:
            sequenced = true;
        case RELIABLE_ORD:
        reliable_ord_packet_label:
            ordered = true;
        case RELIABLE:
        reliable_packet_label:
            actuallySend = false;
            pendPacket = true;
            break;
        }
        fsp.flags |= ((char)(reliablity & 0b111) << 5);

        if(bpacket.dataSz > m_peerMTU) // pend the packet to be sent in fragments
        {
            printf("ArkPeer::sendReliablePacket: sending a packet bigger then MTU (%i bytes sent, mtu is %i)\n", bpacket.dataSz, m_peerMTU);

            int frag_data_sz = m_peerMTU - 64;
            int frag_packets = ceil(bpacket.dataSz / frag_data_sz);
            int compound = m_lastFragmentId++;
            for(int i = 0; i < frag_packets; i++)
            {
                PendingPacket p;
                p.data = new unsigned char[m_peerMTU];
                p.dataSz = m_peerMTU;
                p.sendAtFrame = m_peerFrame;
                p.flags = 0;
                ArkStream fragStream(p.data, p.dataSz);
                fragStream.write<char>(0x80);
                fsp.fragmentCompoundID = compound;
                fsp.fragmentCompoundSize = bpacket.dataSz;
                fsp.fragmentIndex = i;
                fsp.flags |= 1<<3;
                fsp.bitLength = frag_data_sz * 8;
                fsp.frameSetIndex = newFspIndex();
                p.fspIndex = fsp.frameSetIndex;
                printf("fIndex: %i, fCid: %i, fSz: %i, DS: %i, MTU: %i\n", fsp.fragmentIndex, fsp.fragmentCompoundID, fsp.fragmentCompoundSize, frag_data_sz, m_peerMTU);
                fsp.writeToStream(&fragStream);
                for(int _i = 0; _i < frag_data_sz; _i++)
                    fragStream.write(inpackets.read<char>());
                m_pendingPackets.push_front(p);
            }
        }
        else
        {
            bpackets.write<unsigned char>(0x80);
            fsp.writeToStream(&bpackets);
            for(int i = 0; i < inpackets.dataSize(); i++)
                bpackets.write<char>(inpackets.read<char>());

            if(actuallySend)
                sendTo(bpacket.dataSz, bpacket.data, 0);

            if(pendPacket)
            {
                PendingPacket p;
                p.data = new unsigned char[bpacket.dataSz];
                p.dataSz = bpacket.dataSz;
                p.sendAtFrame = m_peerFrame;
                p.fspIndex = fsp.frameSetIndex;
                p.flags = 0;
                memcpy(p.data, bpacket.data, p.dataSz);
                m_pendingPackets.push_front(p);
            }

            if(!actuallySend && !pendPacket)
                printf("ArkPeer::sendReliablePacket: packet not transmitted\n");
        }
    }

    bool ArkPeer::pumpReadPacket(ArkPacket* in_packet)
    {
        ArkStream inStream(in_packet);
        unsigned char packet_type = inStream.read<unsigned char>();
        switch(packet_type)
        {
        default:
            printf("ArkPeer::pumpReadPacket: unknown packet %02x\n", packet_type);
            return false;
        case 0x06: // connection reply 1
            {
                if(m_socket->getSocketStatus() != ARKSOCKET_CONNECTING)
                    return true;
                if(m_connectionStage != 0)
                    return true;

                m_peerMTU = inStream.read<unsigned short>();
                printf("ArkPeer::pumpReadPacket: server received connection request 1, MTU is %i\n", m_peerMTU);
                m_connectionStage = 1;
            }
            break;
        case 0x08: // connection reply 2, we can now get on with our day
            {
                if(m_socket->getSocketStatus() != ARKSOCKET_CONNECTING)
                    return true;
                if(m_connectionStage != 1)
                    return true;

                printf("ArkPeer::pumpReadPacket: received connection reply 2\n");
                m_socket->markConnected();
            }
            break;
        case 0xa0: // nack
            {
                printf("NACK\n");
            }
            break;
        case 0xc0: // ack
            {
                printf("ACK\n");
            }
            break;
        case 0x80: // fsp
            {
                FrameSetPacket fsp;
                fsp.readFromStream(&inStream);
                ArkPacket pdata = inStream.readPacket(in_packet->dataSz - inStream.size());

                int rel_type = 2;
                //int rel_type = fsp.flags >> 5;
                bool fragment = fsp.flags & (1<<3);
                bool gamepacket = true;
                bool packetrecv = true;
                bool listenerev = true;
                switch((PacketReliablity)rel_type)
                {
                case UNRELIABLE:
                    gamepacket = false;
                    break;
                case UNRELIABLE_SEQ:
                    break;
                case RELIABLE:
                    {
                        int fsi = fsp.frameSetIndex;
                        if(fsi > (m_lastRecvFspIndex + 1)) // these are packets in the future
                        {
                            // we are missing packets
                            int missingPackets = fsi - m_lastRecvFspIndex;
                            int fsiStart = fsi - missingPackets;
                            int fsiEnd = fsi + missingPackets;

                            ArkPacket nackPacket(32);
                            ArkStream nackStream(&nackPacket);
                            nackStream.write<char>(0xa0);
                            nackStream.write<char>(true);
                            nackStream.write(fsiStart);
                            nackStream.write(fsiEnd);
                            sendPacket(&nackPacket);

                            printf("NACK range %i->%i\n", fsiStart, fsiEnd);
                        }
                        else if(fsi <= m_lastRecvFspIndex) // already received these packets
                        {
                            packetrecv = false;
                            printf("already received\n");
                            break;
                        }

                        m_lastRecvFspIndex++;
                        printf("ACK %i\n", m_lastRecvFspIndex);
                        sendAcknowledge(fsi);
                    }
                    break;
                case RELIABLE_ORD:
                    break;
                case RELIABLE_SEQ:
                    break;
                case UNRELIABLE_ACK:
                    break;
                case RELIABLE_ACK:
                    break;
                case RELIABLE_ORD_ACK:
                    break;
                default:
                    printf("ArkPeer::pumpReadPacket: received a fsp type %i\n", rel_type);
                    throw std::runtime_error("Received bad fsp type");
                    break;
                }

                if(packetrecv)
                {
                    if(fragment)
                    {
                        auto it = m_incomingMegaPackets.find(fsp.fragmentCompoundID);
                        MegaPacket fragMegaPacket;
                        fragMegaPacket.packet = 0;
                        if(it != m_incomingMegaPackets.end())
                        {
                            fragMegaPacket = m_incomingMegaPackets[fsp.fragmentCompoundID];
                        }
                        else
                        {
                            printf("new megapacket\n");
                            fragMegaPacket.packet = new ArkPacket(fsp.fragmentCompoundSize);
                            fragMegaPacket.packetsToBeReceived = fsp.fragmentCompoundSize / (m_peerMTU - 64);
                            fragMegaPacket.packetsReceived = 0;
                            fragMegaPacket.size = fsp.fragmentCompoundSize;
                            m_incomingMegaPackets[fsp.fragmentCompoundID] = fragMegaPacket;
                        }                    

                        if(fragMegaPacket.packet)
                        {
                            printf("f:%i\n", fsp.fragmentIndex);
                            int poff = (m_peerMTU - 64) * fsp.fragmentIndex;
                            if(fragMegaPacket.size < (poff + (m_peerMTU - 64)));
                            {
                                printf("overwrite\n");
                                break;
                            }
                            fragMegaPacket.packetsReceived++;
                            memcpy(fragMegaPacket.packet->data, in_packet->data, fsp.byteLength);
                        }
                        listenerev = false;
                    }            

                    if(listenerev)
                        if(gamepacket)
                            for (auto &listener : m_listeners)
                                listener->onGamePacketReceiving(this, in_packet);
                        else
                            for (auto &listener : m_listeners)
                                listener->onPacketReceiving(this, in_packet);
                }
            }
            break;
        }
        return true;
    }

    void ArkPeer::frame()
    {
        if(m_pendingPackets.size() != 0)
        {
            PendingPacket front = m_pendingPackets.front();
            if(front.sendAtFrame <= m_peerFrame)
            {
                sendTo(front.dataSz, front.data, front.flags);
                front.sendAtFrame += 1000;
            }
        }
        
        m_peerFrame++;
    }

    void ArkPeer::clientPump()
    {
        if (m_socket->getSocketStatus() == ARKSOCKET_CONNECTED ||
            m_socket->getSocketStatus() == ARKSOCKET_CONNECTING)
        {
            ArkAddress remote_addr;
            ArkPacket *in_packet = recvPacket(&remote_addr);
            bool handled = false;
            if (in_packet)
            {
                handled = pumpReadPacket(in_packet);
                if(!handled)
                    for (auto &listener : m_listeners)
                        listener->onPacketReceiving(this, in_packet);
                delete in_packet;
            }

            if(m_socket->getSocketStatus() == ARKSOCKET_CONNECTING)
            {
                if(m_peerFrame > m_nextConnectionAttempt)
                {
                    printf("ArkPeer::clientPump: sending a connection request %i (MTU: %i, attempt %i)\n", m_connectionStage+1, m_peerMTU, m_connectionAttempts);
                    m_nextConnectionAttempt = m_peerFrame + 50;
                    if(m_connectionStage == 0)
                    {
                        ArkPacket connReq(m_peerMTU);
                        ArkStream connStream(&connReq);
                        connStream.write<char>(0x05);
                        connStream.write<char>(PACKET_VERSION);
                        sendPacket(&connReq);
                        m_peerMTU--;
                        m_connectionAttempts++;
                    }
                    else if(m_connectionStage == 1)
                    {
                        ArkPacket connReq(64);
                        ArkStream connStream(&connReq);
                        connStream.write<char>(0x07);
                        sendPacket(&connReq);

                        m_nextConnectionAttempt += 100;
                    }
                }
            }

            frame();
        }
    }

    void ArkPeer::disconnect(std::string reason, bool silent)
    {
        printf("ArkPeer::disconnect: %s: %s\n", m_remote.toString().c_str(), reason.c_str());
        for(auto& listener : m_listeners)
            listener->onDisconnected(this);
        if(!silent)
            if(m_socket->getSocketType() == ARKSOCKET_CLIENT)
            {
                ArkPacket disconnect_packet(64);
                ArkStream disconnect_stream(&disconnect_packet);
                disconnect_stream.write<char>(0x79);
                disconnect_stream.writeString(reason);
                sendPacket(&disconnect_packet);

                m_socket->markDisconnected();
            }
        else
            if(m_socket->getSocketType() == ARKSOCKET_CLIENT)
                m_socket->markDisconnected();
        if(m_socket->getSocketType() == ARKSOCKET_SERVER)
        {
            ArkPacket disconnect_packet(64);
            ArkStream disconnect_stream(&disconnect_packet);
            disconnect_stream.write<char>(0x79);
            disconnect_stream.writeString(reason);
            sendPacket(&disconnect_packet);
        }
    }

    void ArkPeer::sendAcknowledge(int record)
    {
        ArkPacket ackPacket(32);
        ArkStream ackStream(&ackPacket);
        ackStream.write<char>(0xc0);
        ackStream.write<char>(false); // TODO: acknowledge ranges
        ackStream.write<int>(record);
        sendPacket(&ackPacket);
    }
}
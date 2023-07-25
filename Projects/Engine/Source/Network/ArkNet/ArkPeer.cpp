#include <Network/ArkNet/ArkPeer.hpp>
#include <Network/ArkNet/ArkPacketFactory.hpp>
#include <stdexcept>

namespace ArkNet
{
    ArkPeer::ArkPeer(ArkSocket* socket)
    {
        m_socket = socket;

        if(!ArkPacketFactory::singleton())
        {
            ArkPacketFactory* packetFactory = new ArkPacketFactory();
            packetFactory->registerPackets();
        }
    }

    ArkPeer::ArkPeer(ArkAddress remote, ArkSocket* socket)
    {
        m_remote = remote;
        m_socket = socket;
    }

    ArkPeer::~ArkPeer()
    {

    }

    int ArkPeer::recvFrom(int bytes, char* data, ArkAddress* remote, int flags)
    {
        return m_socket->recvFrom(remote, bytes, data, flags);
    }

    int ArkPeer::sendTo(int bytes, char* data, int flags)
    {
        return m_socket->sendTo(&m_remote, bytes, data, flags);
    }

    ArkPacket* ArkPeer::recvPacket(ArkAddress* remote)
    {        
        char packet_id;
        int p_rc = recvFrom(1, &packet_id, NULL, MSG_PEEK);
        if(p_rc == -1)
            return NULL;
        try{
            ArkPacket* new_pak = ArkPacketFactory::singleton()->build(packet_id);
            char* pak_data = (char*)malloc(new_pak->readLength()+1);
            p_rc = recvFrom(new_pak->readLength()+1, pak_data, remote, 0);
            if(p_rc == -1)
            {
                delete new_pak;
                free(pak_data);
                return NULL;
            }
            new_pak->deserialize(pak_data+1, new_pak->readLength());

            return new_pak;
        } catch(std::runtime_error e)
        {
            printf("ArkPeer::recvPacket: error on receive (what:%s)\n",e.what());
        }
        return NULL;
    }

    void ArkPeer::sendPacket(ArkPacket* packet)
    {
        char* data = (char*)malloc(packet->readLength()+1);
        data[0] = packet->packetId();
        packet->serialize(data+1,packet->readLength());
        sendTo(packet->readLength(),data,0);
    }
}
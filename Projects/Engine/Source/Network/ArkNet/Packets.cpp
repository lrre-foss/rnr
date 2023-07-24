#include <Network/ArkNet/Packets.hpp>
#include <string.h>

namespace ArkNet::Packets
{
    int OpenConnectionRequestPacket::readLength()
    {

    }

    void OpenConnectionRequestPacket::serialize(char* output, int length)
    {
        memcpy(output,&PacketData,sizeof(PacketData));
    }

    void OpenConnectionRequestPacket::deserialize(char* input, int length)
    {

    }
};
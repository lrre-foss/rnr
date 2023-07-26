#include <Network/ArkNet/Packets.hpp>
#include <Network/ArkNet/ArkStream.hpp>
#include <string.h>

namespace ArkNet::Packets
{
    int OpenConnectionRequestPacket::packetId()
    {
        return 0x05;
    }

    int OpenConnectionRequestPacket::readLength()
    {
        return 255;
    }

    void OpenConnectionRequestPacket::serialize(char* output, int length)
    {
        ArkStream stream = ArkStream(output, length);
        stream.writeString(playerName);
    }

    void OpenConnectionRequestPacket::deserialize(char* input, int length)
    {
        ArkStream stream = ArkStream(input, length);
        playerName = stream.readString();
    }
};
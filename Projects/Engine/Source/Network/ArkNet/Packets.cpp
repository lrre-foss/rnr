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
    
    int GamePacket::packetId()
    {
        return 0x07;
    }

    int GamePacket::readLength()
    {
        return 255;
    }

    void GamePacket::serialize(char* output, int length)
    {
        ArkStream stream = ArkStream(output, length);
        int max_len = std::min(length, dataPacketLength);
        stream.write(max_len);
        for(int i = 0; i < max_len; i++)
            stream.write(dataPacket[i]);
    }

    void GamePacket::deserialize(char* input, int length)
    {
        ArkStream stream = ArkStream(input, length);
        dataPacketLength = stream.read<int>();
        for(int i = 0; i < dataPacketLength; i++)
            dataPacket[i] = stream.read<char>();
    }
};
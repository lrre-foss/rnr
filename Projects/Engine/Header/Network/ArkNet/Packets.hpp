#pragma once
#include <Network/ArkNet/ArkPacket.hpp>
#include <string>

namespace ArkNet::Packets
{
    class OpenConnectionRequestPacket : public ArkPacket
    {
    public:
        virtual int packetId();
        virtual int readLength();
        virtual void serialize(char* output, int length);
        virtual void deserialize(char* input, int length);

        std::string playerName;
    };

    const int GAME_PACKET_MAX_SIZE = 255;

    class GamePacket : public ArkPacket
    {
    public:
        virtual int packetId();
        virtual int readLength();
        virtual void serialize(char* output, int length);
        virtual void deserialize(char* input, int length);

        int dataPacketLength;
        char dataPacket[GAME_PACKET_MAX_SIZE];
    };
};
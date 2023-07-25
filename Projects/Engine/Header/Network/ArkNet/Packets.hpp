#pragma once
#include <Network/ArkNet/ArkPacket.hpp>

namespace ArkNet::Packets
{
    class OpenConnectionRequestPacket : public ArkPacket
    {
    public:
        virtual int packetId();
        virtual int readLength();
        virtual void serialize(char* output, int length);
        virtual void deserialize(char* input, int length);
    };
};
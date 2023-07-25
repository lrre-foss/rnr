#pragma once

namespace ArkNet
{
    class ArkPacket
    {
    public:
        virtual int packetId() = 0;
        virtual int readLength() = 0;
        virtual void serialize(char* output, int length) = 0;        
        virtual void deserialize(char* input, int length) = 0;
    };

}
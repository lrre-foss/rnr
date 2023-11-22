#pragma once

namespace ArkNet
{
    class ArkStream;

    const char PACKET_VERSION = 11;
    const char OFFLINE_MAGIC[] = {
        (char)0x00, 
        (char)0xff, 
        (char)0xff, 
        (char)0x00, 
        (char)0xfe, 
        (char)0xfe, 
        (char)0xfe, 
        (char)0xfe, 
        (char)0xfd, 
        (char)0xfd, 
        (char)0xfd, 
        (char)0xfd, 
        (char)0x12, 
        (char)0x34, 
        (char)0x56, 
        (char)0x78
    };

    struct ArkPacket
    {
        ArkPacket* owner;
        unsigned char* data;
        int dataSz;

        ArkPacket();
        ArkPacket(int sz);
        ~ArkPacket();

        ArkPacket sub(int start, int sz);
    };

    enum PacketReliablity
    {
        UNRELIABLE,
        UNRELIABLE_SEQ,
        RELIABLE,
        RELIABLE_ORD,
        RELIABLE_SEQ,
        UNRELIABLE_ACK,
        RELIABLE_ACK,
        RELIABLE_ORD_ACK,
    };

    struct FrameSetPacket
    {
    public:
        unsigned int frameSetIndex;
        unsigned char flags;

        unsigned short bitLength;
        unsigned short byteLength;

        unsigned int frameReliableIndex;
        unsigned int frameSequenceIndex;

        unsigned int orderedFrameIndex;
        unsigned char orderedChannel;

        unsigned int fragmentCompoundSize;
        unsigned short fragmentCompoundID;
        unsigned int fragmentIndex;

        void writeToStream(ArkStream* stream);
        void readFromStream(ArkStream* stream);
    };
}
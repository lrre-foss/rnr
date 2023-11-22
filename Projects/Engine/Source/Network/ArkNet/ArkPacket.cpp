#include <Network/ArkNet/ArkPacket.hpp>
#include <Network/ArkNet/ArkStream.hpp>
#include <stdio.h>

namespace ArkNet
{
    ArkPacket::ArkPacket()
    {
        owner = NULL;
        data = NULL;
        dataSz = 0;
    }

    ArkPacket::ArkPacket(int sz)
    {
        owner = NULL;
        data = new unsigned char[sz];
        dataSz = sz;

        memset(data, dataSz, 0);
    }

    ArkPacket::~ArkPacket()
    {
        if(!owner && data)
        {
            delete[] data;
            data = NULL;
        }
    }

    ArkPacket ArkPacket::sub(int start, int sz)
    {
        if(start + sz > dataSz)
            printf("ArkPacket::sub: warning: subpacket is larger then parent packet\n");
        ArkPacket p;
        p.data = data + start;
        p.dataSz = sz;
        p.owner = this;
        return p;
    }

    void FrameSetPacket::writeToStream(ArkStream* stream)
    {
        stream->write<int>(frameSetIndex);
        stream->write<char>(flags);
        stream->write<short>(bitLength);
        stream->write<int>(frameReliableIndex);
        stream->write<int>(frameSequenceIndex);
        stream->write<int>(orderedFrameIndex);
        stream->write<char>(orderedChannel);
        stream->write<int>(fragmentCompoundSize);
        stream->write<short>(fragmentCompoundID);
        stream->write<int>(fragmentIndex); 
    }

    void FrameSetPacket::readFromStream(ArkStream* stream)
    {
        frameSetIndex = stream->read<int>();
        flags = stream->read<char>();
        bitLength = stream->read<short>();
        byteLength = bitLength / 8;
        frameReliableIndex = stream->read<int>();
        frameSequenceIndex = stream->read<int>();
        orderedFrameIndex = stream->read<int>();
        orderedChannel = stream->read<char>();
        fragmentCompoundSize = stream->read<int>();
        fragmentCompoundID = stream->read<short>();
        fragmentIndex = stream->read<int>();
    }
}
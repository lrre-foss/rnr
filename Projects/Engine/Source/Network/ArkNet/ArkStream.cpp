#include <Network/ArkNet/ArkStream.hpp>

namespace ArkNet
{
    ArkStream::ArkStream(unsigned char *data, int data_size)
    {
        m_data = data;
        m_dataSize = data_size;
        m_dataOff = 0;
    }

    ArkStream::ArkStream(ArkPacket* packet)
    {
        m_data = packet->data;
        m_dataSize = packet->dataSz;
        m_dataOff = 0;
    }

    void ArkStream::writeString(std::string val)
    {
        write((unsigned short)val.size());
        for (int i = 0; i < val.size(); i++)
            write(val[i]);
    }

    std::string ArkStream::readString()
    {
        std::string s;
        unsigned short size = read<unsigned short>();
        for (int i = 0; i < size; i++)
            s.push_back(read<char>());
        return s;
    }

    ArkPacket ArkStream::readPacket(int sz)
    {
        ArkPacket p;
        if((m_dataOff + sz) > m_dataSize)
            throw std::runtime_error("Underflow");
        p.data = (m_data + m_dataOff);
        p.dataSz = sz;
        p.owner = (ArkPacket*)-1; // so ~ArkPacket doesnt deallocate it
        m_dataOff += sz;
        return p;
    }

    bool ArkStream::readMagic()
    {
        char magic2[sizeof(OFFLINE_MAGIC)+1] = {0};
        char magic[sizeof(OFFLINE_MAGIC)+1] = {0};
        for(int i = 0; i < sizeof(OFFLINE_MAGIC); i++)
        {
            magic2[i] = OFFLINE_MAGIC[i];            
            magic[i] = read<char>();
        }
        return (strncmp(magic, magic2, sizeof(OFFLINE_MAGIC)+1) == 1);
    }
}
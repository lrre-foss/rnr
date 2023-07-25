#include <Network/ArkNet/ArkStream.hpp>

namespace ArkNet
{
    ArkStream::ArkStream(char* data, int data_size)
    {
        m_data = data;
        m_dataSize = data_size;
        m_dataOff = 0;
    }

    void ArkStream::writeString(std::string val)
    {
        write((unsigned short)val.size());
        for(int i = 0; i < val.size(); i++)
            write((char)val[i]);
    }

    std::string ArkStream::readString()
    {
        std::string s;
        unsigned short size = read<unsigned short>();
        for(int i = 0; i < size; i++)
            s.push_back(read<char>());
        return s;
    }
}
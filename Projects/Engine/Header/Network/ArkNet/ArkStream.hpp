#pragma once
#include <stdexcept>
#include <string.h>

namespace ArkNet
{
    class ArkStream
    {
        char* m_data;
        int m_dataOff;
        int m_dataSize;
    public:
        ArkStream(char* data, int data_size);

        template<typename T>
        void write(T val)
        {
            size_t val_size = sizeof(val);
            if((m_dataOff + val_size) > m_dataSize)
                throw new std::runtime_error("Overflow");
            memcpy(m_data + m_dataOff, &val, val_size);
            m_dataOff += val_size;            
        }

        template<typename T>
        T read()
        {
            size_t val_size = sizeof(T);
            if((m_dataOff - val_size) < 0)
                throw new std::runtime_error("Underflow");
            T* ref = (T*)(m_data + m_dataOff);
            m_dataOff += val_size;
            return *ref;
        }

        void writeString(std::string val);
        std::string readString();
    };
}
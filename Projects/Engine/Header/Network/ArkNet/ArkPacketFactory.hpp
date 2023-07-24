#pragma once
#include <Network/ArkNet/ArkPacket.hpp>
#include <functional>
#include <string>
#include <map>

namespace ArkNet
{
    class ArkPacketFactory
    {
    public:
        void registerPackets();

        typedef std::function<ArkPacket*()> ArkPacketBuilder;
        ArkPacketFactory();

        bool registerPacket(char key, ArkPacketBuilder builder);
        ArkPacket* build(char key);

        static ArkPacketFactory* singleton() { return m_singleton; };

        // default builder
        template <typename Derived>
        static ArkPacket* packetBuilder() { return new Derived(); }
    private:
        static ArkPacketFactory* m_singleton;
        std::map<char, ArkPacketBuilder> m_builders;
    };
}
#include <Network/ArkNet/ArkPacketFactory.hpp>
#include <stdexcept>

#include <Network/ArkNet/Packets.hpp>

namespace ArkNet
{
    ArkPacketFactory* ArkPacketFactory::m_singleton = 0;

    ArkPacketFactory::ArkPacketFactory() : m_builders()
    {
        m_singleton = this;
    }

    bool ArkPacketFactory::registerPacket(ArkPacketBuilder builder)
    {
        ArkPacket* pak = builder();
        printf("ArkPacketFactory::registerPacket: registering packet %02x\n", pak->packetId());
        bool ok = m_builders.insert(std::make_pair(pak->packetId(), builder)).second;        
        delete pak;
        if(!ok)
            printf("ArkPacketFactory::registerPacket: could not register\n");
        return ok;
    }

    ArkPacket* ArkPacketFactory::build(char key)
    {
        auto it = m_builders.find(key);
        if(it == m_builders.end()) 
            throw std::runtime_error("Invalid packet " + std::to_string(key));
        return it->second();
    }   

    void ArkPacketFactory::registerPackets()
    {
        registerPacket(packetBuilder<Packets::OpenConnectionRequestPacket>);
        registerPacket(packetBuilder<Packets::GamePacket>);
    }
}
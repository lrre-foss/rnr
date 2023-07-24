#pragma once
#include <Network/ArkNet/ArkPeer.hpp>
#include <map>

namespace ArkNet
{
    class ArkServer
    {
        ArkPeer* m_peer;
        std::map<std::string, ArkPeer*> m_peers;
    public:
        ArkServer(ArkPeer* server);

        void frame();
    };
}
#include <Network/NetworkPeer.hpp>

namespace RNR
{
    NetworkPeer::NetworkPeer()
    {
        m_socket = new ArkNet::ArkSocket();
        m_peer = m_socket->getLocalPeer();
    }

    NetworkPeer::~NetworkPeer()
    {

    }
}
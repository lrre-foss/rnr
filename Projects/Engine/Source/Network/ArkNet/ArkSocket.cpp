#include <Network/ArkNet/ArkSocket.hpp>
#include <Network/ArkNet/ArkPeer.hpp>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

namespace ArkNet
{
    ArkSocket::ArkSocket()
    {
        m_socketStatus = ARKSOCKET_DISCONNECTED;
        m_sockFd = socket(AF_INET, SOCK_DGRAM, 0);
        if(m_sockFd < 0)
        {
            printf("ArkSocket::ArkSocket: m_sockFd creation failed\n");
        }

        memset(&m_clientAddress, 0, sizeof(ArkAddress));
        m_clientAddress.address_size = sizeof(m_clientAddress.address);
        memset(&m_remoteAddress, 0, sizeof(ArkAddress));
        m_remoteAddress.address_size = sizeof(m_clientAddress.address);

        m_localPeer = new ArkPeer(this);
    }

    ArkSocket::~ArkSocket()
    {
        delete m_localPeer;
        closeSocket();
    }

    void ArkSocket::bindServer(char* ip, int port)
    {
        m_remoteAddress.address.sin_family = AF_INET;
        m_remoteAddress.address.sin_port = htons(port);
        m_remoteAddress.address.sin_addr.s_addr = inet_addr(ip);

        m_localPeer->setRemote(m_remoteAddress);

        m_socketStatus = ARKSOCKET_CONNECTED;
        m_socketType = ARKSOCKET_SERVER;

        if(bind(m_sockFd, (sockaddr*)&m_remoteAddress.address, sizeof(sockaddr_in)) < 0)
        {
            printf("ArkSocket::bindServer: bind failed\n");
            m_socketStatus = ARKSOCKET_DISCONNECTED;
            return;
        }

        printf("ArkSocket::bindServer: bound on %s:%i\n", ip, port);
    }

    void ArkSocket::tryConnect(char* ip, int port)
    {
        m_clientAddress.address.sin_family = AF_INET;
        m_clientAddress.address.sin_port = htons(port);
        m_clientAddress.address.sin_addr.s_addr = inet_addr(ip);

        m_localPeer->setRemote(m_clientAddress);

        m_socketStatus = ARKSOCKET_CONNECTING;
        m_socketType = ARKSOCKET_CLIENT;
        
        printf("ArkSocket::tryConnect: connecting to %s:%i\n", ip, port);
    }

    int ArkSocket::recvFrom(ArkAddress* remote, size_t bytes, char* output, int flags)
    {
        sockaddr* addr = remote ? (sockaddr*)&(remote->address) : NULL;
        socklen_t* len = remote ? (socklen_t*)&(remote->address_size) : NULL;
        int m = recvfrom(m_sockFd, output, bytes, MSG_DONTWAIT | flags, addr, len);
        if(m == -1)
            printf("ArkSocket::recvFrom: failed, errno: %i (%s)\n", errno, strerror(errno));
        return m;
    }

    int ArkSocket::sendTo(ArkAddress* remote, size_t bytes, char* input, int flags)
    {
        int m = sendto(m_sockFd, input, bytes, MSG_DONTWAIT | flags, (sockaddr*)&remote->address, (socklen_t)sizeof(remote->address));
        if(m == -1)
            printf("ArkSocket::sendTo: failed, errno: %i (%s)\n", errno, strerror(errno));
        return m;
    }

    void ArkSocket::closeSocket()
    {
        close(m_sockFd);
    }
}
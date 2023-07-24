#include <stdio.h>
#include <Network/ArkNet/ArkSocket.hpp>
#include <Network/ArkNet/ArkServer.hpp>

int main(int argc, char** argv)
{
    ArkNet::ArkSocket serverSocket = ArkNet::ArkSocket();
    ArkNet::ArkServer server = ArkNet::ArkServer(serverSocket.getLocalPeer());
    ArkNet::ArkSocket clientSocket = ArkNet::ArkSocket();
    serverSocket.bindServer("127.0.0.1",53641);
    clientSocket.tryConnect("127.0.0.1",53641);
    clientSocket.getLocalPeer()->sendTo(13,"HHello World");
    server.frame();
}
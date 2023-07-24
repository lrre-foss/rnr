#pragma once
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

namespace ArkNet
{
    struct ArkAddress
    {
        struct sockaddr_in address;
        size_t address_size;
        
        ArkAddress();
        std::string toString();
    };
}
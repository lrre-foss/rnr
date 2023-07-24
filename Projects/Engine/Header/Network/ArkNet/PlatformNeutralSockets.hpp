#pragma once

#ifdef __unix__
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#define errno WSAGetLastError()
#endif

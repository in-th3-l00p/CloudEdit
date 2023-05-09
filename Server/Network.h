#ifndef SERVER_NETWORK_H
#define SERVER_NETWORK_H

// sockets imports
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif

// socket fd definition
#ifdef _WIN32
using socket_t = SOCKET;
#else
using socket_t = int;
#endif

namespace Network {
    class Server {
    private:
        socket_t sock;

    public:
        Server();
        ~Server();
    };

} // Server

#endif //SERVER_NETWORK_H

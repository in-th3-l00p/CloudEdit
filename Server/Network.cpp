#include <stdexcept>
#include <cstdlib>
#include "Network.h"
#include "Config.h"

namespace Network {
    Server::Server() {
        int iResult;
        // initialization required on windows
#ifdef _WIN32
        LPWSADATA data;
        iResult = WSAStartup(MAKEWORD(2, 2), data);
        if (iResult != 0)
            throw std::runtime_error("WSAStartup failed");
#endif

        // getting the addressInfo info
        struct addrinfo *addressInfo = nullptr, hints;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;
        iResult = getaddrinfo(
                nullptr,
                Config::PORT,
                &hints,
                &addressInfo
        );
        if (iResult != 0)
            throw std::runtime_error("Failed to get address info");

        // creating & configuring the socket
        sock = (socket_t) socket(
                addressInfo->ai_family,
                addressInfo->ai_socktype,
                addressInfo->ai_protocol
        );
#ifdef _WIN32
        if (sock == INVALID_SOCKET) {
            WSACleanup();
#else
        if (sock < 0) {
#endif
            freeaddrinfo(addressInfo);
            throw std::runtime_error("Failed to initialize server's socket");
        }
        if (setsockopt(
                sock, SOL_SOCKET, SO_REUSEADDR,
                (char*)&Config::YES, sizeof (Config::YES))  )

        freeaddrinfo(addressInfo);
    }

    Server::~Server() {
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        shutdown(sock, 2);
#endif
    }
} // Server
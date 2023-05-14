#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#ifdef _WIN32
#include "windows.h"
#endif

namespace Config {
    constexpr char PORT[] = "5000";
#ifdef _WIN32
    constexpr int YES = 1;
#else
    constexpr BOOL YES = TRUE;
#endif
    constexpr int MAX_CONNECTIONS = 3;
} // Config

#endif //SERVER_CONFIG_H

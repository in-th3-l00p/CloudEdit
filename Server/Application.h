#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include "Network.h"

/*
 * The entry point of the application.
 * Starts the server's logic
 * */
class Application {
private:
    bool running = true;
    Network::Server server;

public:
    Application();
    ~Application();
    void run();
};


#endif //SERVER_APPLICATION_H

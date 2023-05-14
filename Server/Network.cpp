#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include "Network.h"
#include "Config.h"

namespace Network {
    inline id_t generator = 0;

    Server::Server()
        : clientContainer(new Container::BSTClientContainer())
    {
        int iResult;
        // initialization required on windows
#ifdef _WIN32
        WSADATA data;
        iResult = WSAStartup(MAKEWORD(2, 2), &data);
        if (iResult != 0)
            throw std::runtime_error(
                    std::string("WSAStartup failed ") +
                    std::to_string(iResult)
                    );
#endif

        // getting the addressInfo info
        struct addrinfo *addressInfo = nullptr, hints;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET; // TODO: permit IPv6 too
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
        if (SOCKET_INVALID(sock)) {
#ifdef _WIN32
            WSACleanup();
#endif
            freeaddrinfo(addressInfo);
            throw std::runtime_error("Failed to initialize server's socket");
        }
        iResult = setsockopt(
                sock, SOL_SOCKET, SO_REUSEADDR,
                (char*)&Config::YES, sizeof (Config::YES));
        if (iResult != 0) {
            freeaddrinfo(addressInfo);
            throw std::runtime_error(
                    std::string("Failed to set socket options ") +
                    std::to_string(iResult)
                    );
        }

        iResult = bind(sock, addressInfo->ai_addr, (int) addressInfo->ai_addrlen);
        if (iResult != 0) {
            freeaddrinfo(addressInfo);
            throw std::runtime_error("Failed to bind to the socket");
        }

        freeaddrinfo(addressInfo);

        removeThread = std::thread{ &Server::removeHandle, this };
    }

    Server::~Server() {
        removeThread.join();
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        shutdown(sock, 2);
#endif
    }

    void Server::run() {
        if (listen(sock, Config::MAX_CONNECTIONS) != 0)
            throw std::runtime_error("Failed to start listening");
        while (running)
        {
             socket_t clientSock = accept(sock, nullptr, nullptr);
             if (SOCKET_INVALID(clientSock)) {
                 running = false;
                 throw std::runtime_error("Failed to accept a new client");
             }

             containerMutex.lock();
             auto* client = new Client(
                     clientSock,
                     running,
                     [this](id_t id) {
                         removals.push(id);
                     } );
             clientContainer->add(client);
             containerMutex.unlock();
        }
    }

    void Server::removeHandle() {
        while (running) {
            while (!removals.empty()) {
                id_t id = removals.back(); removals.pop();
                containerMutex.lock();
                clientContainer->remove(id);
                containerMutex.unlock();
            }
        }
    }

    Client::Client(
            socket_t sock,
            const bool& serverRunning,
            std::function<void(id_t)> onDisconnect
            )
        : id(generator++),
        serverRunning(serverRunning)
        {
        this->sock = sock;
        this->thread = std::thread{ &Client::handle, this };
        this->onDisconnect = std::move(onDisconnect);
    }

    Client::~Client() {
        thread.join();
#ifdef _WIN32
        closesocket(sock);
#else
        shutdown(sock, 2);
#endif
    }

    void Client::handle() const {
        std::cout << "new client connected\n";
        char buffer[1024];
        int result;
        while (serverRunning) {
            result = recv(sock, buffer, 1024, 0);
            if (result == 0) {
                std::cout << "client disconnected\n";
                break;
            } else if (SOCKET_INVALID(result))
                throw std::runtime_error("Error on reading data from a client");
            if (SOCKET_INVALID(send(sock, "hello", 6, 0)))
                throw std::runtime_error("Error on sending data to a client");
            std::cout << buffer << '\n';
        }

        onDisconnect(id);
    }

    const id_t &Client::getId() const {
        return id;
    }

    namespace Container {
        BSTClientContainer::~BSTClientContainer() {
            // iterative preorder
            std::stack<BSTClientNode*> trace;
            BSTClientNode* current = root;
            while (root) {
                trace.push(root);
                root = root->left;
            }

            while (!trace.empty()) {
                delete(trace.top()); trace.pop();
                if (trace.top()->right) {
                    current = trace.top()->right;
                    while (current && current->left) {
                        trace.push(current);
                        current = current->left;
                    }
                }
            }
        }

        BSTClientContainer::BSTClientNode::BSTClientNode(Client* client) {
            this->client = client;
        }

        BSTClientContainer::BSTClientNode::~BSTClientNode() {
            delete client;
        }

        void BSTClientContainer::add(Client* client) {
            if (root == nullptr) {
                root = new BSTClientNode(client);
                count++;
                return;
            }
            BSTClientNode *prev = nullptr, *current = root;
            while (current) {
                prev = current;
                if (client->getId() > current->client->getId())
                    current = current->right;
                else if (client->getId() < current->client->getId())
                    current = current->left;
                else
                    throw std::runtime_error("Client with the same id already exists");
            }

            if (client->getId() > prev->client->getId())
                prev->right = new BSTClientNode(client);
            else
                prev->left = new BSTClientNode(client);
            count++;
        }

        const Client &BSTClientContainer::get(
                BSTClientContainer::BSTClientNode *current,
                const id_t &id
                ) const {
            if (current == nullptr)
                throw std::runtime_error("Client not found");
            if (current->client->getId() == id)
                return *current->client;
            if (id > current->client->getId())
                return get(current->right, id);
            return get(current->left, id);
        }

        const Client &BSTClientContainer::get(id_t id) const {
            return get(root, id);
        }

        const int BSTClientContainer::getCount() const {
            return count;
        }

        BSTClientContainer::BSTClientNode *BSTClientContainer::remove(
                BSTClientNode* current,
                const id_t &id
                ) const {
            if (current == nullptr)
                return nullptr;
            if (id > current->client->getId())
                current->right = remove(current->right, id);
            else if (id < current->client->getId())
                current->left = remove(current->left, id);
            else {
                if (current->left == nullptr && current->right == nullptr) {
                    delete current;
                    return nullptr;
                }

                if (current->left == nullptr) {
                    BSTClientNode* node = current->right;
                    delete current;
                    return node;
                } else if (current->right == nullptr) {
                    BSTClientNode* node = current->left;
                    delete current;
                    return node;
                }

                BSTClientNode* maximum = current->left;
                while (maximum->right)
                    maximum = maximum->right;
                delete(current->client);
                current->client = maximum->client;
                current->left = remove(
                        current->left,
                        current->client->getId()
                        );
            }

            return current;
        }

        void BSTClientContainer::remove(id_t id) {
            root = remove(root, id);
            count--;
        }

        Client &BSTClientContainer::Iterator::operator*() const {
            if (trace.empty())
                throw std::runtime_error("Iterator finished");
            return *trace.top()->client;
        }

        BSTClientContainer::Iterator::pointer BSTClientContainer::Iterator::operator->() const {
            if (trace.empty())
                return nullptr;
            return trace.top()->client;
        }

        BSTClientContainer::Iterator &BSTClientContainer::Iterator::operator++() {
            if (trace.empty())
                return *this;
            BSTClientNode* current = trace.top()->right;
            trace.pop();
            while (current) {
                trace.push(current);
                current = current->left;
            }
            return *this;
        }

        BSTClientContainer::Iterator BSTClientContainer::Iterator::operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const BSTClientContainer::Iterator &a, const BSTClientContainer::Iterator &b) {
            if (a.trace.empty() || b.trace.empty())
                return a.trace.empty() && b.trace.empty();
            return a.trace.top() == b.trace.top();
        }

        bool operator!=(const BSTClientContainer::Iterator &a, const BSTClientContainer::Iterator &b) {
            return !(a == b);
        }

        BSTClientContainer::Iterator BSTClientContainer::begin() {
            return Iterator(root);
        }

    }
} // Server
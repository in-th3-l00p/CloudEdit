#ifndef SERVER_NETWORK_H
#define SERVER_NETWORK_H

// stl thangss
#include <thread>
#include <memory>
#include <stack>
#include <queue>
#include <functional>

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
#define SOCKET_INVALID(s) s == INVALID_SOCKET
#else
using socket_t = int;
#define SOCKET_INVALID(s) s < 0
#endif

using id_t = unsigned long long;

namespace Network {
    class Client {
    private:
        static std::mutex mutex;

        id_t id{};
        socket_t sock;
        std::thread thread;
        const bool& serverRunning;
        std::function<void(id_t)> onDisconnect;

    public:
        void handle() const;
        [[nodiscard]] const id_t& getId() const;

        Client(
                socket_t sock,
                const bool& serverRunning,
                std::function<void(id_t)> onDisconnect
                );
        ~Client();
    };

    namespace Container {
        class ClientContainer {
        public:
            virtual void add(Client* client) = 0;
            virtual const Client& get(id_t id) const = 0;
            virtual const int getCount() const = 0;
            virtual void remove(id_t id) = 0;
            virtual ~ClientContainer() = default;
        };


        // todo: implement red black trees
        class BSTClientContainer: public ClientContainer {
        private:
            struct BSTClientNode {
                Client* client = nullptr;
                BSTClientNode *left = nullptr, *right = nullptr;

                BSTClientNode() = default;
                explicit BSTClientNode(Client* client);
                ~BSTClientNode();
            };

            int count = 0;
            BSTClientNode* root = nullptr;

            const Client& get(BSTClientNode* current, const id_t& id) const;
            BSTClientNode* remove(BSTClientNode* current, const id_t& id) const;

        public:
            ~BSTClientContainer() override;

            void add(Client* client) override;
            [[nodiscard]] const Client& get(id_t id) const override;
            const int getCount() const override;
            void remove(id_t id) override;

            struct Iterator {
                using iterator_category = std::forward_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = Client;
                using pointer = Client*;
                using reference = Client&;
            private:
                std::stack<BSTClientNode*> trace;
            public:
                explicit Iterator(BSTClientNode* root) {
                    while (root) {
                        trace.push(root);
                        root = root->left;
                    }
                }

                reference operator*() const;
                pointer operator->() const;
                Iterator& operator++();
                Iterator operator++(int);

                friend bool operator==(const Iterator& a, const Iterator& b);
                friend bool operator!=(const Iterator& a, const Iterator& b);
            };

            Iterator begin();
            static Iterator end() {
                return Iterator(nullptr);
            }
        };
    }

    class Server {
    private:
        socket_t sock;
        bool running = true;
        std::unique_ptr<Container::ClientContainer> clientContainer;
        std::mutex containerMutex;

        // queue where client removals are handled
        std::queue<id_t> removals;
        std::thread removeThread;
        void removeHandle();

    public:
        Server();
        ~Server();
        void run();
    };
} // Network

#endif //SERVER_NETWORK_H

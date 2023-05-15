#ifndef APPLICATION_NAMECONTAINER_H
#define APPLICATION_NAMECONTAINER_H

#include <stack>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <cstring>

namespace Container {
    // implemented as a bst
    // todo: make it a red black
    template<typename T>
    class NameContainer {
    public:
        struct Node {
            T* event;
            Node *left = nullptr, *right = nullptr;

            explicit Node(T* event = nullptr) {
                this->event = event;
            }
        };

        struct Iterator {
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

        private:
            std::stack<Node*> trace;

        public:
            explicit Iterator(Node* root) {
                if (root == nullptr)
                    return;
                trace.push(root);
                while (root->left) {
                    trace.push(root->left);
                    root = root->left;
                }
            }

            Iterator(const Iterator& other) {
                trace = other.trace;
            }

            Iterator(Iterator&& other) noexcept {
                trace = std::move(other.trace);
            }

            pointer operator->() {
                if (trace.empty())
                    return nullptr;
                return trace.top()->event;
            }

            reference operator*() {
                if (trace.empty())
                    throw std::runtime_error("Iterator is empty");
                return *trace.top()->event;
            }

            Iterator& operator++() {
                if (trace.empty())
                    throw std::runtime_error("Iterator is empty");
                Node* current = trace.top();
                trace.pop();

                if (current->right) {
                    trace.push(current->right);
                    Node* aux = current->right;
                    while (aux->left) {
                        trace.push(aux->left);
                        aux = aux->left;
                    }
                }

                return *this;
            }

            Iterator operator++(int) {
                Iterator result = *this;
                ++(*this);
                return result;
            }

            bool operator==(const Iterator& other) const {
                return trace == other.trace;
            }

            bool operator!=(const Iterator& other) const {
                return !(*this == other);
            }

            Iterator& operator=(const Iterator& other) {
                trace = other.trace;
                return *this;
            }

            Iterator& operator=(Iterator&& other) noexcept {
                trace = std::move(other.trace);
                return *this;
            }
        };

    private:
        Node* root = nullptr;
        size_t count = 0;

        Node* remove(Node* current, const std::string& name) {
            if (current == nullptr)
                throw std::runtime_error("Event doesn't exist");
            int result = strcmp(name.c_str(), current->event->name.c_str());
            if (result < 0)
                current->left = remove(current->left, name);
            else if (result > 0)
                current->right = remove(current->right, name);
            else {
                if (current->left == nullptr && current->right == nullptr) {
                    delete current;
                    count--;
                    return nullptr;
                }

                if (current->left == nullptr) {
                    Node* aux = current->left;
                    delete current;
                    count--;
                    return nullptr;
                } else if (current->right == nullptr) {
                    Node* aux = current->right;
                    delete current;
                    count--;
                    return nullptr;
                }

                Node* maximum = current->left;
                while (maximum->right)
                    maximum = maximum->right;
                current->event = maximum->event;
                current->left = remove(current->left, current->event->name);
                count--;
            }

            return current;
        }

    public:
        NameContainer() = default;
        ~NameContainer() {
            std::stack<Node*> trace;
            trace.push(root);

            while (!trace.empty()) {
                Node* current = trace.top();
                trace.pop();
                if (current->left)
                    trace.push(current->left);
                if (current->right)
                    trace.push(current->right);
                delete current;
            }
        }

        T& get(const std::string& name) {
            Node* current = root;
            int result = strcmp(name.c_str(), current->event->name.c_str());
            while (result) {
                if (result < 0) {
                    current = current->left;
                } else {
                    current = current->right;
                }
                if (!current)
                    throw std::runtime_error("Event doesn't exist");
                result = strcmp(name.c_str(), current->event->name.c_str());
            }

            return *current->event;
        }

        [[nodiscard]] const size_t& getCount() const {
            return count;
        }

        void add(T* event) {
            if (root == nullptr) {
                root = new Node(event);
                count++;
                return;
            }

            int result;
            Node *last = nullptr, *current = root;
            while (current) {
                result = strcmp(event->name.c_str(), current->event->name.c_str());
                last = current;
                if (result == 0)
                    throw std::runtime_error("Event with the same name already exists");
                else if (result < 0)
                    current = current->left;
                else
                    current = current->right;
            }
            if (result < 0)
                last->left = new Node(event);
            else
                last->right = new Node(event);
            count++;
        }

        void remove(const std::string& name) {
            root = remove(root, name);
        }

        Iterator begin() {
            return Iterator(root);
        }

        Iterator end() {
            return Iterator(nullptr);
        }
    };
} // Container

#endif //APPLICATION_NAMECONTAINER_H

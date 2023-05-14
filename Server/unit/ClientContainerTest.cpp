#include <string>
#include "gtest/gtest.h"
#include "Network.h"

class BSTContainerTest: public ::testing::Test {
protected:
    bool serverRunning = false;
    Network::Client *client1, *client2, *client3;
    Network::Container::BSTClientContainer* container;

    void SetUp() override {
        client1 = new Network::Client(1337, serverRunning, [](id_t) {});
        client2 = new Network::Client(69, serverRunning, [](id_t) {});
        client3 = new Network::Client(420, serverRunning, [](id_t) {});
        container = new Network::Container::BSTClientContainer();
        container->add(client1);
        container->add(client2);
        container->add(client3);
    }
};

TEST_F(BSTContainerTest, Iterate) {
    auto iterator = container->begin();
    EXPECT_EQ(&(*iterator), client1);
    iterator++;
    EXPECT_EQ(&(*iterator), client2);
    iterator++;
    EXPECT_EQ(&(*iterator), client3);
    iterator++;
    EXPECT_EQ(iterator, container->end());
    iterator++;
    EXPECT_EQ(iterator, container->end());
}

TEST_F(BSTContainerTest, Counting) {
    EXPECT_EQ(container->getCount(), 3);
}

TEST_F(BSTContainerTest, Getting) {
    EXPECT_EQ(client1, &container->get(client1->getId()));
    EXPECT_EQ(client2, &container->get(client2->getId()));
    EXPECT_EQ(client3, &container->get(client3->getId()));
}

TEST_F(BSTContainerTest, Deleting) {
    id_t id = client1->getId();
    container->remove(client1->getId());
    EXPECT_EQ(container->getCount(), 2);
    EXPECT_ANY_THROW(container->get(id));
}
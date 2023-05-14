#include "gtest/gtest.h"
#include "Network.h"

class ClientTest: public ::testing::Test {
protected:
    bool serverRunning = true;
    Network::Client *client1, *client2, *client3;

    void SetUp() override {
        client1 = new Network::Client(1337, serverRunning);
        client2 = new Network::Client(69, serverRunning);
        client3 = new Network::Client(420, serverRunning);
    }
};

TEST_F(ClientTest, IdGenerator) {
    EXPECT_EQ(client1->getId(), 0)
        << "Client1 has id of "
        << client1->getId()
        << ", while it should be "
        << 0;
    EXPECT_EQ(client2->getId(), 1)
        << "Client2 has id of "
        << client2->getId()
        << ", while it should be "
        << 1;
    EXPECT_EQ(client3->getId(), 2)
        << "Client3 has id of "
        << client3->getId()
        << ", while it should be "
        << 2;
}
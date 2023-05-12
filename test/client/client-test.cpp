#include "captidom-client-common/client/client.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "client/version.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace captidom;

using ::testing::_;
using ::testing::Matcher;

class MockTransport : public ITransport
{
public:
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, send, (const WakeupBroadcastMessage *message), (const override));
    MOCK_METHOD(void, send, (const WakeupMessage *message), (const override));

    void receiveWakeupBroadcast()
    {
        WakeupBroadcastMessage request;
        this->receiver->onMessageReceived(&request);
    }
};

TEST(client, respondToWakeupBroadcast)
{
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    MockTransport transport;

    Client *client = new Client(platform, ip, &transport);

    WakeupBroadcastMessage request;
    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(_))).Times(1);
    transport.receiveWakeupBroadcast();

    delete client;
}
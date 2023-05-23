#include "captidom-client-common/client/client.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "captidom-client-common/proto-v1/describe-message.h"
#include "captidom-client-common/proto-v1/describe-request-message.h"
#include "client/version.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace captidom;

using ::testing::_;
using ::testing::Matcher;

MATCHER_P(WakeupMessageEquals, other, "Equality matcher for type WakeupMessage")
{
    EXPECT_TRUE(0 == strcmp(arg->getPlatform(), other->getPlatform())) << "Expected platform \"" << other->getPlatform() << "\" got \"" << arg->getPlatform() << "\"";
    EXPECT_TRUE(0 == strcmp(arg->getIp(), other->getIp())) << "Expected ip \"" << other->getIp() << "\" got \"" << arg->getIp() << "\"";
    EXPECT_TRUE(0 == strcmp(arg->getVersion(), other->getVersion())) << "Expected version \"" << other->getVersion() << "\" got \"" << arg->getVersion() << "\"";
}

MATCHER_P(DescribeMessageEquals, other, "Equality matcher for type DescribeMessage")
{
    EXPECT_TRUE(0 == strcmp(arg->getDeviceId(), other->getDeviceId())) << "Expected hwInfo \"" << other->getDeviceId() << "\" got \"" << arg->getDeviceId() << "\"";
}

class MockTransport : public ITransport
{
public:
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, send, (const WakeupBroadcastMessage *message), (const override));
    MOCK_METHOD(void, send, (const WakeupMessage *message), (const override));
    MOCK_METHOD(void, send, (const DescribeMessage *message), (const override));

    void receiveWakeupBroadcast()
    {
        WakeupBroadcastMessage request;
        this->receiver->onMessageReceived(&request);
    }

    void receiveDescribeRequest()
    {
        DescribeRequestMessage request;
        this->receiver->onMessageReceived(&request);
    }
};

TEST(client, respondToWakeupBroadcast)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    MockTransport transport;
    const WakeupMessage response(platform, ip, CAPTIDOM_CLIENT_VERSION);

    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(WakeupMessageEquals(&response)))).Times(1);

    Client *client = new Client(deviceId, platform, ip, &transport);

    WakeupBroadcastMessage request;

    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(WakeupMessageEquals(&response)))).Times(1);

    transport.receiveWakeupBroadcast();

    delete client;
}

TEST(client, sendsWakeupOnStart)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    MockTransport transport;
    const WakeupMessage response(platform, ip, CAPTIDOM_CLIENT_VERSION);

    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(WakeupMessageEquals(&response)))).Times(1);

    Client *client = new Client(deviceId, platform, ip, &transport);

    delete client;
}

TEST(client, respondToDescribe)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    MockTransport transport;
    const WakeupMessage wakeupResponse(platform, ip, CAPTIDOM_CLIENT_VERSION);
    const DescribeMessage describeResponse(deviceId);

    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(WakeupMessageEquals(&wakeupResponse)))).Times(1);
    EXPECT_CALL(
        transport,
        send(Matcher<const DescribeMessage *>(DescribeMessageEquals(&describeResponse))))
        .Times(1);

    Client *client = new Client(deviceId, platform, ip, &transport);

    transport.receiveDescribeRequest();

    delete client;
}
#include "captidom-client-common/client/client.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "captidom-client-common/proto-v1/describe-message.h"
#include "captidom-client-common/proto-v1/describe-request-message.h"
#include "client/version.h"
#include "mock-transport.h"
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

TEST(clientWakeup, respondToWakeupBroadcast)
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

TEST(clientWakeup, sendsWakeupOnStart)
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
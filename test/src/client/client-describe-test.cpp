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

MATCHER_P(DescribeMessageEquals, other, "Equality matcher for type DescribeMessage")
{
    EXPECT_TRUE(0 == strcmp(arg->getDeviceId(), other->getDeviceId())) << "Expected hwInfo \"" << other->getDeviceId() << "\" got \"" << arg->getDeviceId() << "\"";
    EXPECT_EQ(arg->getChannels()->getCount(), other->getChannels()->getCount()) << "Expected channelCount \"" << other->getChannels()->getCount() << "\" got \"" << arg->getChannels()->getCount() << "\"";
}

TEST(clientDescribe, respondToDescribe)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";
    ChannelList list(0, 0);

    MockTransport transport;
    const DescribeMessage describeResponse(deviceId, &list);

    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(_))).Times(1);
    EXPECT_CALL(
        transport,
        send(Matcher<const DescribeMessage *>(DescribeMessageEquals(&describeResponse))))
        .Times(1);

    Client *client = new Client(deviceId, platform, ip, &transport);

    transport.receiveDescribeRequest();

    delete client;
}
#include "captidom-client-common/client/client.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "captidom-client-common/proto-v1/describe-message.h"
#include "captidom-client-common/proto-v1/describe-request-message.h"
#include "captidom-client-common/client/version.h"
#include "mock-transport.h"
#include "matchers/describe-message-matcher.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace captidom;

using ::testing::_;
using ::testing::Matcher;

TEST(clientDescribe, respondToDescribe_noChannels)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";
    ChannelList list(0, 0);

    MockTransport transport;
    const DescribeMessage describeResponse(deviceId, &list);

    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(_))).Times(0);
    EXPECT_CALL(
        transport,
        send(Matcher<const DescribeMessage *>(DescribeMessageEquals(&describeResponse))))
        .Times(1);

    Client *client = new Client(deviceId, platform, ip, &transport);

    transport.receiveDescribeRequest();

    delete client;
}

namespace
{
    captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN};
    captidom::ChannelMode pollModes[] = {captidom::ChannelMode::CHANNEL_MODE_POLL};
}

TEST(clientDescribe, respondToDescribe)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    const UnprovisionedChannel *ch1 = new captidom::UnprovisionedChannel(990, "test", 4, types, 1, pollModes, 1);
    const UnprovisionedChannel *array[1] = {ch1};
    ChannelList list(array, 1);

    MockTransport transport;
    const DescribeMessage describeResponse(deviceId, &list);
    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(_))).Times(0);
    EXPECT_CALL(
        transport,
        send(Matcher<const DescribeMessage *>(DescribeMessageEquals(&describeResponse))))
        .Times(1);

    Client *client = new Client(deviceId, platform, ip, &transport, array, 1);

    transport.receiveDescribeRequest();

    delete client;
    delete ch1;
}
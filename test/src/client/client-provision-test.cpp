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

namespace
{
    captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN};
    captidom::ChannelMode pollModes[] = {captidom::ChannelMode::CHANNEL_MODE_POLL};
}

TEST(clientWakeup, receiveProvision)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    const int channelId = 990;

    MockTransport transport;

    const UnprovisionedChannel *ch1 = new captidom::UnprovisionedChannel(channelId, "test", 4, types, 1, pollModes, 1);
    const UnprovisionedChannel *channelArray[1] = {ch1};

    Client *client = new Client(deviceId, platform, ip, &transport, channelArray, 1);

    ChannelList list(channelArray, 1);
    const DescribeMessage describeResponse(deviceId, &list);

    ProvisionMessage requestThatDoesNotExist(1);
    transport.receiveProvisionMessage(&requestThatDoesNotExist);

    ProvisionMessage requestThatExists(channelId);
    transport.receiveProvisionMessage(&requestThatDoesNotExist);

    delete client;
}
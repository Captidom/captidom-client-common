#include "captidom-client-common/client/client.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "captidom-client-common/proto-v1/describe-message.h"
#include "captidom-client-common/proto-v1/describe-request-message.h"
#include "captidom-client-common/client/version.h"
#include "mock-transport.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace captidom;

using ::testing::_;
using ::testing::Matcher;

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

    MockTransport transport;

    const UnprovisionedChannel *ch1 = new captidom::UnprovisionedChannel(990, "test", 4, types, 1, pollModes, 1);
    const UnprovisionedChannel *channelArray[1] = {ch1};

    Client *client = new Client(deviceId, platform, ip, &transport, channelArray, 1);

    ProvisionMessage request(1);

    transport.receiveProvisionMessage(&request);

    delete client;
}
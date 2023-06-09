#include "captidom-client-common/client/client.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "captidom-client-common/proto-v1/describe-message.h"
#include "captidom-client-common/proto-v1/describe-request-message.h"
#include "captidom-client-common/client/version.h"
#include "mock-transport.h"
#include "mock-channel-factory.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace captidom;

using ::testing::Matcher;

MATCHER_P(ProvisionMessageEquals, other, "Equality matcher for type ProvisionMessage")
{
    EXPECT_EQ(arg->getChannelId(), other->getChannelId());
    EXPECT_EQ(arg->getChannelType(), other->getChannelType());
    return true;
}

namespace
{
    captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN};
    captidom::ChannelMode pollModes[] = {captidom::ChannelMode::CHANNEL_MODE_POLL};
}

TEST(clientProvision, provisionFailForUnknownChannel)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    const int channelId = 990;

    MockTransport transport;
    MockChannelFactory chFactory;

    const UnprovisionedChannel *ch1 = new captidom::UnprovisionedChannel(channelId, "test", 4, types, 1, pollModes, 1);
    const UnprovisionedChannel *channelArray[1] = {ch1};

    Client *client = new Client(deviceId, platform, ip, &transport, channelArray, 1, &chFactory);

    ProvisionMessage::Description description = {.input = {.mode = ChannelMode::CHANNEL_MODE_POLL}};

    ChannelList list(channelArray, 1);
    ProvisionMessage requestThatDoesNotExist(1, ChannelType::CHANNEL_TYPE_ANALOG_IN, description);
    EXPECT_CALL(
        chFactory,
        createInputChannel(ProvisionMessageEquals(&requestThatDoesNotExist)))
        .Times(0);

    transport.receiveProvisionMessage(&requestThatDoesNotExist);

    delete client;
}

TEST(clientProvision, provisionFailForChannelWithUnsupportedType)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    const int channelId = 990;

    MockTransport transport;
    MockChannelFactory chFactory;

    const UnprovisionedChannel *ch1 = new captidom::UnprovisionedChannel(channelId, "test", 4, types, 1, pollModes, 1);
    const UnprovisionedChannel *channelArray[1] = {ch1};

    Client *client = new Client(deviceId, platform, ip, &transport, channelArray, 1, &chFactory);

    ChannelList list(channelArray, 1);

    ProvisionMessage::Description description = {.input = {.mode = ChannelMode::CHANNEL_MODE_POLL}};

    ProvisionMessage requestThatIsNotSupported(channelId, ChannelType::CHANNEL_TYPE_DIGITAL_IN, description);
    EXPECT_CALL(
        chFactory,
        createInputChannel(ProvisionMessageEquals(&requestThatIsNotSupported)))
        .Times(0);
    transport.receiveProvisionMessage(&requestThatIsNotSupported);

    delete client;
}

TEST(clientProvision, provisionOKForInputChannel)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    const int channelId = 990;

    MockTransport transport;
    MockChannelFactory chFactory;

    const UnprovisionedChannel *ch1 = new captidom::UnprovisionedChannel(channelId, "test", 4, types, 1, pollModes, 1);
    const UnprovisionedChannel *channelArray[1] = {ch1};

    Client *client = new Client(deviceId, platform, ip, &transport, channelArray, 1, &chFactory);

    ChannelList list(channelArray, 1);

    ProvisionMessage::Description description = {.input = {.mode = ChannelMode::CHANNEL_MODE_POLL}};

    ProvisionMessage requestThatExists(channelId, ChannelType::CHANNEL_TYPE_ANALOG_IN, description);
    EXPECT_CALL(
        chFactory,
        createInputChannel(ProvisionMessageEquals(&requestThatExists)))
        .Times(1);
    transport.receiveProvisionMessage(&requestThatExists);

    delete client;
}

TEST(clientProvision, provisionFailWithUnsupportedMode)
{
    const char *deviceId = "SOMEID";
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    const int channelId = 990;

    MockTransport transport;
    MockChannelFactory chFactory;

    const UnprovisionedChannel *ch1 = new captidom::UnprovisionedChannel(channelId, "test", 4, types, 1, pollModes, 1);
    const UnprovisionedChannel *channelArray[1] = {ch1};

    Client *client = new Client(deviceId, platform, ip, &transport, channelArray, 1, &chFactory);

    ChannelList list(channelArray, 1);

    ProvisionMessage::Description description = {.input = {.mode = ChannelMode::CHANNEL_MODE_PUSH}};

    ProvisionMessage requestThatExists(channelId, ChannelType::CHANNEL_TYPE_ANALOG_IN, description);
    EXPECT_CALL(
        chFactory,
        createInputChannel(ProvisionMessageEquals(&requestThatExists)))
        .Times(0);
    transport.receiveProvisionMessage(&requestThatExists);

    delete client;
}
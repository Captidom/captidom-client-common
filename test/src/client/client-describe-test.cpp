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

bool compareChannelLists(const ChannelList *a, const ChannelList *b)
{
    EXPECT_EQ(a->getCount(), b->getCount());

    for (int i = 0; i < a->getCount(); i++)
    {
        const UnprovisionedChannel **aCh = a->getItem(i);
        const UnprovisionedChannel **bCh = b->getItem(i);
        EXPECT_EQ((*aCh)->getId(), (*bCh)->getId()) << "Expected id for channel " << i << " \"" << (*aCh)->getId() << "\" got \"" << (*bCh)->getId() << "\"";
        const char *aName;
        int aLength = 0;
        const char *bName;
        int bLength = 0;
        (*aCh)->getName(&aName, aLength);
        (*bCh)->getName(&bName, bLength);
        EXPECT_STREQ(aName, bName) << "Expected name for channel " << i << " \"" << aName << "\" got \"" << bName << "\"";

        const List<ChannelMode> *aModes = (*aCh)->getSupportedModes();
        const List<ChannelMode> *bModes = (*bCh)->getSupportedModes();

        EXPECT_EQ(aModes->getCount(), bModes->getCount()) << "Expected supported modes for channel " << i << " \"" << aModes->getCount() << "\" got \"" << bModes->getCount() << "\"";
        for (int j = 0; j < aModes->getCount(); j++)
        {
            EXPECT_TRUE(bModes->contains(aModes->getItem(j))) << "Expected mode " << *aModes->getItem(j) << " to be supported for channel " << i;
            EXPECT_TRUE((*bCh)->supportsMode(*aModes->getItem(j))) << "Expected mode " << *aModes->getItem(j) << " to be supported for channel " << i;
        }

        const List<ChannelType> *aTypes = (*aCh)->getSupportedTypes();
        const List<ChannelType> *bTypes = (*bCh)->getSupportedTypes();

        EXPECT_EQ(aTypes->getCount(), bTypes->getCount()) << "Expected supported modes for channel " << i << " \"" << aTypes->getCount() << "\" got \"" << bModes->getCount() << "\"";
        for (int j = 0; j < aTypes->getCount(); j++)
        {
            EXPECT_TRUE(bTypes->contains(aTypes->getItem(j))) << "Expected type " << *aTypes->getItem(j) << " to be supported for channel " << i;
            EXPECT_TRUE((*bCh)->supportsType(*aTypes->getItem(j))) << "Expected type " << *aTypes->getItem(j) << " to be supported for channel " << i;
        }
    }

    return true;
}

MATCHER_P(DescribeMessageEquals, other, "Equality matcher for type DescribeMessage")
{
    EXPECT_TRUE(0 == strcmp(arg->getDeviceId(), other->getDeviceId())) << "Expected hwInfo \"" << other->getDeviceId() << "\" got \"" << arg->getDeviceId() << "\"";
    EXPECT_TRUE(compareChannelLists(arg->getChannels(), other->getChannels()));
}

TEST(clientDescribe, respondToDescribe_noChannels)
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
    EXPECT_CALL(transport, send(Matcher<const WakeupMessage *>(_))).Times(1);
    EXPECT_CALL(
        transport,
        send(Matcher<const DescribeMessage *>(DescribeMessageEquals(&describeResponse))))
        .Times(1);

    Client *client = new Client(deviceId, platform, ip, &transport, array, 1);

    transport.receiveDescribeRequest();

    delete client;
}
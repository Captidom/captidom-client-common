#pragma once

#include "captidom-client-common/client/client.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace captidom;

using ::testing::Matcher;

bool compareChannelLists(const ChannelList *a, const ChannelList *b);

MATCHER_P(DescribeMessageEquals, other, "Equality matcher for type DescribeMessage")
{
    EXPECT_TRUE(0 == strcmp(arg->getDeviceId(), other->getDeviceId())) << "Expected hwInfo \"" << other->getDeviceId() << "\" got \"" << arg->getDeviceId() << "\"";
    EXPECT_TRUE(compareChannelLists(arg->getChannels(), other->getChannels()));

    return true;
}
#pragma once

#include "captidom-client-common/proto-v1/base-message.h"
#include "captidom-client-common/channel/channel-list.h"

namespace captidom
{
    class DescribeMessage : BaseMessage
    {
        char *deviceId;
        const ChannelList *channels;

    public:
        DescribeMessage(const char *const deviceId, const ChannelList *const channels);
        ~DescribeMessage();

        const char *const getDeviceId() const;
        const ChannelList *const getChannels() const;
    };
}
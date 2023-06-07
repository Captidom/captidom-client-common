#pragma once

#include "captidom-client-common/proto-v1/base-message.h"
#include "captidom-client-common/channel/channel-type.h"

namespace captidom
{
    class ProvisionMessage : BaseMessage
    {

    private:
        int channelId;
        ChannelType channelType;

    public:
        ProvisionMessage(int channelId, ChannelType channelType);
        ~ProvisionMessage();

        int getChannelId() const;
        ChannelType getChannelType() const;
    };
}
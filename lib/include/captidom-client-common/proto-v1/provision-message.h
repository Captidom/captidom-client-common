#pragma once

#include "captidom-client-common/proto-v1/base-message.h"
#include "captidom-client-common/channel/channel-type.h"
#include "captidom-client-common/channel/channel-mode.h"

namespace captidom
{
    class ProvisionMessage : BaseMessage
    {
    public:
        struct InputDescription
        {
            ChannelMode mode;
        };

        struct OutputDescription
        {
            int value;
        };

        union Description
        {
            InputDescription input;
            OutputDescription output;
        };

    private:
        int channelId;
        ChannelType channelType;
        Description description;

    public:
        ProvisionMessage(int channelId, ChannelType channelType, Description &description);
        ~ProvisionMessage();

        int getChannelId() const;
        ChannelType getChannelType() const;
        const Description * getDescription() const;
    };
}
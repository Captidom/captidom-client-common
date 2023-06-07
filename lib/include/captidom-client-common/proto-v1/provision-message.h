#pragma once

#include "captidom-client-common/proto-v1/base-message.h"

namespace captidom
{
    class ProvisionMessage : BaseMessage
    {

    private:
        int channelId;

    public:
        ProvisionMessage(int channelId);
        ~ProvisionMessage();

        int getChannelId() const;
    };
}
#pragma once

#include "captidom-client-common/channel/input-channel.h"
#include "captidom-client-common/channel/output-channel.h"
#include "captidom-client-common/proto-v1/provision-message.h"

namespace captidom
{
    class ChannelFactory
    {
    public:
        ChannelFamily getChannelFamily(const ProvisionMessage *message) const;
        virtual InputChannel *createInputChannel(const ProvisionMessage *message) const = 0;
        virtual OutputChannel *createOutputChannel(const ProvisionMessage *message) const = 0;
    };
}
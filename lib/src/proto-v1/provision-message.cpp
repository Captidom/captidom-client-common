#include "captidom-client-common/proto-v1/provision-message.h"
#include "captidom-client-common/client/version.h"
#include <cstdlib>
#include <cstring>

namespace captidom
{
    ProvisionMessage::ProvisionMessage(int channelId, ChannelType channelType) : channelId(channelId), channelType(channelType), BaseMessage(MessageType::ProvisionMessageType){};

    ProvisionMessage::~ProvisionMessage()
    {
    }

    int ProvisionMessage::getChannelId() const
    {
        return this->channelId;
    };

    ChannelType ProvisionMessage::getChannelType() const
    {
        return this->channelType;
    };
}
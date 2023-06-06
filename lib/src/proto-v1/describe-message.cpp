#include "captidom-client-common/proto-v1/describe-message.h"
#include <cstdlib>
#include <cstring>

namespace captidom
{
    DescribeMessage::DescribeMessage(const char *const deviceId, const ChannelList *const channels) : BaseMessage(MessageType::DescribeMessageType)
    {
        this->deviceId = (char *)malloc(sizeof(char *) * strlen(deviceId + 1));
        memcpy(this->deviceId, deviceId, strlen(deviceId) + 1);

        this->channels = channels;
    };

    DescribeMessage::~DescribeMessage()
    {
        free(this->deviceId);
    }

    const char *const DescribeMessage::getDeviceId() const
    {
        return this->deviceId;
    }

    const ChannelList *const DescribeMessage::getChannels() const
    {
        return this->channels;
    }
}
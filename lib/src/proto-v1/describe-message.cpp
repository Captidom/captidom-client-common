#include "proto-v1/describe-message.h"
#include <cstdlib>
#include <cstring>

namespace captidom
{
    DescribeMessage::DescribeMessage(const char *const deviceId) : BaseMessage(MessageType::DescribeMessageType)
    {
        this->deviceId = (char *)malloc(sizeof(char *) * strlen(deviceId + 1));
        memcpy(this->deviceId, deviceId, strlen(deviceId) + 1);
    };

    DescribeMessage::~DescribeMessage()
    {
        free(this->deviceId);
    }

    const char *const DescribeMessage::getDeviceId() const
    {
        return this->deviceId;
    }
}
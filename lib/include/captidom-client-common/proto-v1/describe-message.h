#pragma once

#include "proto-v1/base-message.h"

namespace captidom
{
    class DescribeMessage : BaseMessage
    {
        char *deviceId;

    public:
        DescribeMessage(const char *const deviceId);
        ~DescribeMessage();

        const char *const getDeviceId() const;
    };
}
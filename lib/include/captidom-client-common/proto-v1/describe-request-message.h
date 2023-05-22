#pragma once

#include "proto-v1/base-message.h"

namespace captidom
{
    class DescribeRequestMessage : BaseMessage
    {
    public:
        DescribeRequestMessage() : BaseMessage(MessageType::DescribeRequestMessageType){};
    };
}
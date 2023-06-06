#pragma once

#include "captidom-client-common/proto-v1/base-message.h"

namespace captidom
{
    class DescribeRequestMessage : BaseMessage
    {
    public:
        DescribeRequestMessage() : BaseMessage(MessageType::DescribeRequestMessageType){};
    };
}
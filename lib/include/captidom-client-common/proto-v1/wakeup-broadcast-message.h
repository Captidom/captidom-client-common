#pragma once

#include "captidom-client-common/proto-v1/base-message.h"

namespace captidom
{
    class WakeupBroadcastMessage : BaseMessage
    {
    public:
        WakeupBroadcastMessage() : BaseMessage(MessageType::WakeupBroadcastMessageType){};
    };
}
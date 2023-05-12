#pragma once

#include "proto-v1/wakeup-broadcast-message.h"
#include "proto-v1/wakeup-message.h"

namespace captidom
{
    class IReceiver
    {
    public:
        virtual void onMessageReceived(WakeupBroadcastMessage *request) const = 0;
    };
}
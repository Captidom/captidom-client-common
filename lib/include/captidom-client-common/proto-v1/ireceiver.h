#pragma once

#include "captidom-client-common/proto-v1/wakeup-broadcast-message.h"
#include "captidom-client-common/proto-v1/describe-request-message.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"

namespace captidom
{
    class IReceiver
    {
    public:
        virtual void onMessageReceived(WakeupBroadcastMessage *request) const = 0;
        virtual void onMessageReceived(DescribeRequestMessage *request) const = 0;
    };
}
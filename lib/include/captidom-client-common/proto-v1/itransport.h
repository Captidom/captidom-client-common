#pragma once

#include "proto-v1/wakeup-broadcast-message.h"
#include "proto-v1/wakeup-message.h"
#include "proto-v1/describe-message.h"
#include "proto-v1/ireceiver.h"

namespace captidom
{
    class ITransport
    {
    protected:
        const IReceiver *receiver = 0;

    public:
        void setReceiver(const IReceiver *receiver);

        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void send(const WakeupBroadcastMessage *message) const = 0;
        virtual void send(const WakeupMessage *message) const = 0;
        virtual void send(const DescribeMessage *message) const = 0;
    };
}
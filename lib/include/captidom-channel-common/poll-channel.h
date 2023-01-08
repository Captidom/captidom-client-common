#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "push-channel.h"
#include "channel-value-callback.h"

namespace captidom
{

    class PollChannel : virtual public PushChannel
    {
    private:
        int pollIntervalSeconds = 0;

    public:
        PollChannel();
        virtual void setPollingInterval(int pollInterval);
        int getPollingInterval();
    };
}
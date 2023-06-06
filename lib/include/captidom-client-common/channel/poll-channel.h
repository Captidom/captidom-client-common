#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "captidom-client-common/channel/input-channel.h"
#include "captidom-client-common/channel/channel-value-callback.h"

namespace captidom
{

    class PollChannel : virtual public InputChannel
    {
    private:
        int pollIntervalSeconds = 0;

    public:
        PollChannel();
        virtual void setPollingInterval(int pollInterval);
        int getPollingInterval();
    };
}
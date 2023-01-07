#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "input-channel.h"
#include "poll-channel-config.h"
#include "channel-value-callback.h"

namespace captidom
{

    class PollChannel : virtual public InputChannel
    {
    private:
        int pollIntervalSeconds = 0;

    public:
        PollChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes);
        void setPollingInterval(int pollInterval);
    };
}
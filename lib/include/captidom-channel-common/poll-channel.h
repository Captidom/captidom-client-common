#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "input-channel.h"
#include "poll-channel-config.h"
#include "channel-value-callback.h"

namespace captidom
{

    template<class T_DATA_TYPE>
    class PollChannel : public InputChannel<T_DATA_TYPE>
    {
    private:
        int pollIntervalSeconds = 0;
    public:
        PollChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes);

        void setConfig(PollChannelConfig *config);
        const PollChannelConfig getConfig();
    };
}

#include "poll-channel.hpp"
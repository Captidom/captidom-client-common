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
    class PollChannel : public PushChannel<T_DATA_TYPE>
    {
    private:
        int pollIntervalSeconds = 0;
    public:
        void setConfig(PollChannelConfig *config);
    };
}

#include "poll-channel.hpp"
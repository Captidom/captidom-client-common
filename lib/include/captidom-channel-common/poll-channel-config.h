#pragma once

#include "channel-type.h"
#include "channel-mode.h"

namespace captidom {

    struct PollChannelConfig {
        ChannelType type;
        ChannelMode mode;
        int pollIntervalSeconds;
    };
}
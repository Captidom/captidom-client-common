#pragma once

#include "channel-config.h"

namespace captidom {

    struct PollChannelConfig : ChannelConfig {
        int pollIntervalSeconds;
    };
}
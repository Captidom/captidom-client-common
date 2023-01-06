#pragma once

#include "channel-type.h"
#include "channel-mode.h"

namespace captidom {

    struct ChannelConfig {
        ChannelType type;
        ChannelMode mode;
    };
}
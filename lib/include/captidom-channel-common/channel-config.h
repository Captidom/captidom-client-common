#pragma once

#include "channel-type.h"
#include "channel-mode.h"

namespace captidom {

    struct ChannelConfig {
        ChannelType type;
        ChannelMode mode;

        bool operator==(const ChannelConfig& rhs) const
        {
            return this->type == rhs.type && this->mode == rhs.mode;
        }

    };
}
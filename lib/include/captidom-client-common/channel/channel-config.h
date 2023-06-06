#pragma once

#include "captidom-client-common/channel/channel-type.h"
#include "captidom-client-common/channel/channel-mode.h"

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
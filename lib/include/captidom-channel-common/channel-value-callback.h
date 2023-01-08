#pragma once

#include "base-channel.h"

namespace captidom {

    struct ChannelValueCallback {
        void *context;
        void (*callback)(void * context, const char *, int channelId);
    };

    static captidom::ChannelValueCallback EMPTY_CHANNEL_VALUE_CALLBACK = {0, 0};
}
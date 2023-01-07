#pragma once

#include "channel.h"

namespace captidom {

    struct ChannelValueCallback {
        void *context;
        void (*callback)(void * context, const char *, Channel *);
    };
}
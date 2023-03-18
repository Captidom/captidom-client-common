#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include <string.h>

#include "list.h"
#include "channel-config.h"

namespace captidom
{

    class BaseProvisionedChannel
    {
    public:

        virtual ChannelType getType() = 0;
        virtual ChannelMode getMode() = 0;
    };
}
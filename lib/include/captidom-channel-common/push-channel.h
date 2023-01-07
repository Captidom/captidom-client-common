#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "input-channel.h"
#include "channel-value-callback.h"

namespace captidom
{

    class PushChannel : virtual public InputChannel
    {
    protected:
        ChannelValueCallback *newValueCB = 0;

    public:
        PushChannel(ChannelValueCallback *newValueCB, int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes);
        ~PushChannel(){};
    };
}
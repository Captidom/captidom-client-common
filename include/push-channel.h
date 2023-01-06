#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "channel.h"

namespace captidom
{

    class PushChannel : public Channel
    {
    protected:
        ChannelValueCallback *newValueCB = 0;

    public:
        PushChannel(ChannelValueCallback *newValueCB, int id, char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes);
        ~PushChannel(){};
    };
}
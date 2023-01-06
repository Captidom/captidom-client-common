#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "input-channel.h"
#include "channel-value-callback.h"

namespace captidom
{

    template<class T_DATA_TYPE>
    class PushChannel : public InputChannel<T_DATA_TYPE>
    {
    protected:
        ChannelValueCallback *newValueCB = 0;

    public:
        PushChannel(ChannelValueCallback *newValueCB, int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes);
        ~PushChannel(){};
    };
}

#include "push-channel.hpp"
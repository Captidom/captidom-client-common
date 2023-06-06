#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "captidom-client-common/channel/input-channel.h"
#include "captidom-client-common/channel/channel-value-callback.h"

namespace captidom
{

    class PushChannel : virtual public InputChannel
    {
    protected:
        ChannelValueCallback *newValueCB = 0;

    public:
        PushChannel(ChannelValueCallback *newValueCB);
        ~PushChannel();

        const char * getValue() override;
    };
}
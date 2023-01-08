#pragma once

#include "io-channel.h"
#include "poll-channel.h"

namespace captidom
{
    class UniversalChannel : virtual public IOChannel, virtual public PollChannel, virtual public PushChannel
    {
    public:
        UniversalChannel(){};
    };
}
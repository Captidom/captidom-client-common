#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "input-channel.h"

namespace captidom
{

    class IOChannel : virtual public InputChannel
    {
    public:
        IOChannel() {};
        virtual void setValue(const char *strValue, int strValueLen) = 0;
    };
}
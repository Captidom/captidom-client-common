#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "channel.h"

namespace captidom
{
    class InputChannel : virtual public Channel
    {
    protected:
        char serializedValue[64];

        virtual void produceValue(char *serializedValue) = 0;

    public:
        InputChannel() {};
        const char * getValue();
    };
}

#include "input-channel.hpp"
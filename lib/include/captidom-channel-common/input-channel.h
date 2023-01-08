#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "base-channel.h"

namespace captidom
{
    class InputChannel : virtual public BaseChannel
    {
    protected:
        char serializedValue[64];

        virtual void produceValue(char *serializedValue) = 0;

    public:
        InputChannel() {};
        virtual const char * getValue();
    };
}
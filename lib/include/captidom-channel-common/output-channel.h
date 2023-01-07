#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "input-channel.h"

namespace captidom
{

    class IOutputChannel : virtual public InputChannel
    {
    public:
        virtual void setValue(const char *strValue, int strValueLen) = 0;
    };
}
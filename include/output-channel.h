#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "channel.h"

namespace captidom
{

    class OutputChannel : public Channel
    {
    public:
        virtual void setValue(const char *strValue, int strValueLen) = 0;
    };
}
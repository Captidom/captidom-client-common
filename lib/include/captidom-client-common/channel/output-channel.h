#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "input-channel.h"
#include "base-provisioned-channel.h"

namespace captidom
{

    class OutputChannel : virtual public BaseChannel, virtual public BaseProvisionedChannel
    {
    public:
        OutputChannel() {};
        virtual void setValue(const char *strValue, int strValueLen) = 0;
    };
}
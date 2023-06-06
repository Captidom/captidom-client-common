#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "captidom-client-common/channel/input-channel.h"
#include "captidom-client-common/channel/base-provisioned-channel.h"

namespace captidom
{

    class OutputChannel : virtual public BaseChannel, virtual public BaseProvisionedChannel
    {
    public:
        OutputChannel() {};
        virtual void setValue(const char *strValue, int strValueLen) = 0;
    };
}
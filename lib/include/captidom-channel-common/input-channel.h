#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "channel.h"

namespace captidom
{

    class InputChannel : public Channel
    {
    protected:
        char serializedValue[64];

        virtual void produceValue(char *serializedValue) = 0;

    public:
        InputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedmodes, int maxModes);

        const char * getValue();
    };
}

#include "input-channel.hpp"
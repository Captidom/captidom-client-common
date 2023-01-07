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
        List<char> *serializedValue = 0;

        virtual void produceValue(List<char> **serializedValue) = 0;

    public:
        InputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedmodes, int maxModes);
        ~InputChannel();

        void getValue(const char **strValue, int &strValueLen);
    };
}

#include "input-channel.hpp"
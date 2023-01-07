#pragma once

#include "input-channel.h"

namespace captidom
{
    InputChannel::InputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedModes, int maxModes) : Channel(id, name, nameLength, supportedTypes, maxTypes, supportedModes, maxModes)
    {
    }

    const char * InputChannel::getValue()
    {
        this->produceValue(this->serializedValue);
        return this->serializedValue;
    }
}
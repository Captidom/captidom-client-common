#pragma once

#include "input-channel.h"

namespace captidom
{
    InputChannel::InputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedModes, int maxModes) : Channel(id, name, nameLength, supportedTypes, maxTypes, supportedModes, maxModes)
    {
        this->serializedValue = new List<char>("", 0);
    }

    InputChannel::~InputChannel()
    {
        delete this->serializedValue;
    }

    void InputChannel::getValue(const char **value, int &valueLen)
    {
        this->produceValue(&this->serializedValue);
        this->serializedValue->getItems(value, valueLen);
    }
}
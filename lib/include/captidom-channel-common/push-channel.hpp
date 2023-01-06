#pragma once

#include "push-channel.h"

namespace captidom
{
    const ChannelMode modes[] = {ChannelMode::CHANNEL_MODE_PUSH};

    template <class T_DATA_TYPE>
    PushChannel<T_DATA_TYPE>::PushChannel(ChannelValueCallback *newValueCB, int id, char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes) : InputChannel<T_DATA_TYPE>(id, name, nameLength, supportedTypes, maxTypes, modes, 1)
    {
        this->newValueCB = newValueCB;
    }
}
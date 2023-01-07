#pragma once

#include "push-channel.h"

namespace captidom
{
    const ChannelMode modes[] = {ChannelMode::CHANNEL_MODE_PUSH};

    PushChannel::PushChannel(ChannelValueCallback *newValueCB, int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes) : InputChannel(id, name, nameLength, supportedTypes, maxTypes, modes, 1)
    {
        this->newValueCB = newValueCB;
    }
}
#pragma once

#include "input-channel.h"

namespace captidom
{
    const char * InputChannel::getValue()
    {
        this->produceValue(this->serializedValue);
        return this->serializedValue;
    }
}
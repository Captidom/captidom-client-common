#pragma once

#include "poll-channel.h"

namespace captidom
{
    template <class T_DATA_TYPE>
    void PollChannel<T_DATA_TYPE>::setConfig(PollChannelConfig *config)
    {
        this->pollIntervalSeconds = config->pollIntervalSeconds;
        Channel::setConfig(config);
    }
}
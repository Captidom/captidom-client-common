#pragma once

#include "poll-channel.h"

namespace captidom
{
    const ChannelMode modes[] = {ChannelMode::CHANNEL_MODE_POLL};

    template <class T_DATA_TYPE>
    PollChannel<T_DATA_TYPE>::PollChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes) : InputChannel<T_DATA_TYPE>(id, name, nameLength, supportedTypes, maxTypes, modes, 1){};

    template <class T_DATA_TYPE>
    void PollChannel<T_DATA_TYPE>::setPollingInterval(int pollInterval) {
        this->pollIntervalSeconds = pollInterval;
    }
}
#pragma once

#include "poll-channel.h"

namespace captidom
{
    template <class T_DATA_TYPE>
    PollChannel<T_DATA_TYPE>::PollChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes) : InputChannel<T_DATA_TYPE>(newValueCB, id, name, nameLength, supportedTypes, maxTypes){};

    template <class T_DATA_TYPE>
    void PollChannel<T_DATA_TYPE>::setConfig(PollChannelConfig *config)
    {
        this->pollIntervalSeconds = config->pollIntervalSeconds;
        ChannelConfig chConfig = {
            config->type,
            config->mode,
        };
        Channel::setConfig(&chConfig);
    }

    template <class T_DATA_TYPE>
    const PollChannelConfig PollChannel<T_DATA_TYPE>::getConfig()
    {
        const ChannelConfig *chConfig = Channel::getConfig();
        return {
            chConfig->type,
            chConfig->mode,
            this->pollIntervalSeconds,
        };
    }
}
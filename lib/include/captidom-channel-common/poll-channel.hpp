#pragma once

#include "poll-channel.h"

namespace captidom
{
    const ChannelMode modes[] = {ChannelMode::CHANNEL_MODE_POLL};

    PollChannel::PollChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes) : Channel(id, name, nameLength, supportedTypes, maxTypes, modes, 1){};

    void PollChannel::setPollingInterval(int pollInterval) {
        this->pollIntervalSeconds = pollInterval;
    }
}
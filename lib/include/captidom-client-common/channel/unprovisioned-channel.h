#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include <string.h>

#include "captidom-client-common/util/list.h"
#include "captidom-client-common/channel/base-channel.h"
#include "captidom-client-common/channel/channel-config.h"

namespace captidom
{

    class UnprovisionedChannel : public virtual BaseChannel
    {
    private:
        List<ChannelType> *supportedTypes;
        List<ChannelMode> *supportedModes;

    public:
        UnprovisionedChannel(int id, const char *name, int nameLength, ChannelType *supportedTypes, int maxTypes, ChannelMode *supportedModes, int maxModes);

        ~UnprovisionedChannel();

        const List<ChannelType> *getSupportedTypes() const;
        bool supportsType(ChannelType type) const;
        const List<ChannelMode> * getSupportedModes() const;
        bool supportsMode(ChannelMode mode) const;
    };
}
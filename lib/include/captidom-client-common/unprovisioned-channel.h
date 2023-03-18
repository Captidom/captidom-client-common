#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include <string.h>

#include "list.h"
#include "base-channel.h"
#include "channel-config.h"

namespace captidom
{

    class UnprovisionedChannel : public virtual BaseChannel
    {
    private:
        List<ChannelType> *supportedTypes;
        List<ChannelMode> *supportedModes;

    public:
        UnprovisionedChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedModes, int maxModes);

        ~UnprovisionedChannel();

        void getSupportedTypes(const ChannelType **supportedTypes, int &maxTypes);
        bool supportsType(ChannelType type);
        void getSupportedModes(const ChannelMode **supportedModes, int &maxModes);
        bool supportsMode(ChannelMode mode);
    };
}
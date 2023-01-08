#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include <string.h>

#include "list.h"
#include "channel-config.h"

namespace captidom
{

    class BaseChannel
    {
    private:
        int id;

        List<char> *name;
        List<ChannelType> *supportedTypes;
        List<ChannelMode> *supportedModes;

        ChannelConfig config = {
            ChannelType::CHANNEL_TYPE_NONE,
            ChannelMode::CHANNEL_MODE_NONE,
        };

    protected:
        virtual void applyConfig(const ChannelConfig *config) = 0;

    public:
        BaseChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedModes, int maxModes);

        ~BaseChannel();

        void getName(const char **destination, int &length);

        int getId();

        void getSupportedTypes(const ChannelType **supportedTypes, int &maxTypes);
        bool supportsType(ChannelType type);
        void getSupportedModes(const ChannelMode **supportedModes, int &maxModes);
        bool supportsMode(ChannelMode mode);

        bool setConfig(const ChannelConfig *config);

        const ChannelConfig *getConfig();
    };
}
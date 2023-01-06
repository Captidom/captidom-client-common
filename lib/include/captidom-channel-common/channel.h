#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include <string.h>

#include "list.h"
#include "channel-config.h"
#include "channel-value-callback.h"

namespace captidom
{

    class Channel
    {
    private:
        int id;

        List<char> *name;
        List<ChannelType> *supportedTypes;
        List<ChannelMode> *supportedModes;

    public:
        Channel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedModes, int maxModes);

        ~Channel();

        void getName(const char **destination, int &length);

        int getId();

        void getSupportedTypes(const ChannelType **supportedTypes, int &maxTypes);
        void getSupportedModes(const ChannelMode **supportedModes, int &maxModes);
    };
}
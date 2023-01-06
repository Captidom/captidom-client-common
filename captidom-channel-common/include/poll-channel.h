#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "channel.h"

namespace captidom
{

    class PollChannel : public Channel
    {
    protected:
        List<char> *value;

    public:
        PollChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes);
        ~PollChannel();
        void getValue(const char **strValue, int &strValueLen);
    };
}
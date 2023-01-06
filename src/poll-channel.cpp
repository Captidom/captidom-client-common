#include "poll-channel.h"

namespace captidom
{
    const ChannelMode modes[] = {ChannelMode::CHANNEL_MODE_PUSH};

    PollChannel::PollChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes) : Channel(id, name, nameLength, supportedTypes, maxTypes, modes, 1)
    {
        this->value = new List<char>("", 0);
    }

    PollChannel::~PollChannel()
    {
        delete this->value;
    }

    void PollChannel::getValue(const char **value, int &valueLen)
    {
        this->value->getItems(value, valueLen);
    }
}
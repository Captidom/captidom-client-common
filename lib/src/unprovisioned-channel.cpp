#include "unprovisioned-channel.h"

namespace captidom
{
    UnprovisionedChannel::UnprovisionedChannel(int id, const char *name, int nameLength, ChannelType supportedTypes[], int numTypes, ChannelMode supportedModes[], int numModes) : BaseChannel(id, name, nameLength)
    {
        this->supportedTypes = new List<ChannelType>(supportedTypes, numTypes);
        this->supportedModes = new List<ChannelMode>(supportedModes, numModes);
    }

    UnprovisionedChannel::~UnprovisionedChannel()
    {
        delete this->supportedModes;
        delete this->supportedTypes;
    }

    const List<ChannelType> *UnprovisionedChannel::getSupportedTypes()
    {
        return this->supportedTypes;
    }

    bool UnprovisionedChannel::supportsType(ChannelType type)
    {

        if (ChannelType::CHANNEL_TYPE_NONE == type)
        {
            return true;
        }

        return this->getSupportedTypes()->contains(&type);
    }

    const List<ChannelMode> * UnprovisionedChannel::getSupportedModes()
    {
        return this->supportedModes;
    }

    bool UnprovisionedChannel::supportsMode(ChannelMode mode)
    {

        if (ChannelMode::CHANNEL_MODE_NONE == mode)
        {
            return true;
        }

        return this->getSupportedModes()->contains(&mode);
    }
}
#include "unprovisioned-channel.h"

namespace captidom
{
    UnprovisionedChannel::UnprovisionedChannel(int id, const char *name, int nameLength, const ChannelType supportedTypes[], int numTypes, const ChannelMode supportedModes[], int numModes) : BaseChannel(id, name, nameLength)
    {
        this->supportedTypes = new List<ChannelType>(supportedTypes, numTypes);
        this->supportedModes = new List<ChannelMode>(supportedModes, numModes);
    }

    UnprovisionedChannel::~UnprovisionedChannel()
    {
        delete this->supportedModes;
        delete this->supportedTypes;
    }

    void UnprovisionedChannel::getSupportedTypes(const ChannelType **supportedTypes, int &maxTypes)
    {
        this->supportedTypes->getItems(supportedTypes, maxTypes);
    }

    bool UnprovisionedChannel::supportsType(ChannelType type)
    {

        if (ChannelType::CHANNEL_TYPE_NONE == type)
        {
            return true;
        }

        const ChannelType *types;
        int numTypes;
        this->getSupportedTypes(&types, numTypes);

        for (int i = 0; i < numTypes; i++)
        {
            if (types[i] == type)
            {
                return true;
            }
        }

        return false;
    }

    void UnprovisionedChannel::getSupportedModes(const ChannelMode **supportedModes, int &maxModes)
    {
        this->supportedModes->getItems(supportedModes, maxModes);
    }

    bool UnprovisionedChannel::supportsMode(ChannelMode mode)
    {

        if (ChannelMode::CHANNEL_MODE_NONE == mode)
        {
            return true;
        }

        const ChannelMode *modes;
        int numModes;
        this->getSupportedModes(&modes, numModes);

        for (int i = 0; i < numModes; i++)
        {
            if (modes[i] == mode)
            {
                return true;
            }
        }

        return false;
    }
}
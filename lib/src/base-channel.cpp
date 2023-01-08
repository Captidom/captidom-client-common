#include "base-channel.h"

namespace captidom
{
    BaseChannel::BaseChannel(int id, const char *name, int nameLength, const ChannelType supportedTypes[], int numTypes, const ChannelMode supportedModes[], int numModes)
    {
        this->id = id;

        this->name = new List<char>(name, nameLength);
        this->supportedTypes = new List<ChannelType>(supportedTypes, numTypes);
        this->supportedModes = new List<ChannelMode>(supportedModes, numModes);
    }

    BaseChannel::~BaseChannel()
    {
        delete this->supportedModes;
        delete this->supportedTypes;
        delete this->name;
    }

    int BaseChannel::getId()
    {
        return this->id;
    }

    void BaseChannel::getName(const char **destination, int &length)
    {
        this->name->getItems(destination, length);
    }

    void BaseChannel::getSupportedTypes(const ChannelType **supportedTypes, int &maxTypes)
    {
        this->supportedTypes->getItems(supportedTypes, maxTypes);
    }

    bool BaseChannel::supportsType(ChannelType type)
    {
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

    void BaseChannel::getSupportedModes(const ChannelMode **supportedModes, int &maxModes)
    {
        this->supportedModes->getItems(supportedModes, maxModes);
    }

    bool BaseChannel::supportsMode(ChannelMode mode)
    {
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

    bool BaseChannel::setConfig(const ChannelConfig *config)
    {

        if (!this->supportsType(config->type) || !this->supportsMode(config->mode))
        {
            return false;
        }

        this->config = *config;

        this->applyConfig(config);

        return true;
    }

    const ChannelConfig *BaseChannel::getConfig()
    {
        return &this->config;
    }
}
#include "channel.h"

namespace captidom
{
    Channel::Channel(int id, const char *name, int nameLength, const ChannelType supportedTypes[], int numTypes, const ChannelMode supportedModes[], int numModes)
    {
        this->id = id;

        this->name = new List<char>(name, nameLength);
        this->supportedTypes = new List<ChannelType>(supportedTypes, numTypes);
        this->supportedModes = new List<ChannelMode>(supportedModes, numModes);
    }

    Channel::~Channel()
    {
        delete this->supportedModes;
        delete this->supportedTypes;
        delete this->name;
    }

    int Channel::getId()
    {
        return this->id;
    }

    void Channel::getName(const char **destination, int &length)
    {
        this->name->getItems(destination, length);
    }

    void Channel::getSupportedTypes(const ChannelType **supportedTypes, int &maxTypes)
    {
        this->supportedTypes->getItems(supportedTypes, maxTypes);
    }

    void Channel::getSupportedModes(const ChannelMode **supportedModes, int &maxModes)
    {
        this->supportedModes->getItems(supportedModes, maxModes);
    }
}
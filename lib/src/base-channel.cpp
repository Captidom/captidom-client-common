#include "base-channel.h"

namespace captidom
{
    BaseChannel::BaseChannel(int id, const char *name, int nameLength)
    {
        this->id = id;

        this->name = new List<char>(name, nameLength);
    }

    BaseChannel::~BaseChannel()
    {
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
}
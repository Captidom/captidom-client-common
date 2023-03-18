#include "base-channel.h"

namespace captidom
{
    BaseChannel::BaseChannel(int id, const char *name, int nameLength)
    {
        this->id = id;

        this->name = name;
        this->nameLength = nameLength;
    }

    BaseChannel::~BaseChannel()
    {
    }

    int BaseChannel::getId()
    {
        return this->id;
    }

    void BaseChannel::getName(const char **destination, int &length)
    {
        *destination = this->name;
        length = this->nameLength;
    }
}
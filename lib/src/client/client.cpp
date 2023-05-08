#include "client/client.h"

namespace captidom
{
    Client::Client(const UnprovisionedChannel **channels, int numChannels)
    {
        this->channels = new ChannelList(channels, numChannels);
    }

    Client::~Client()
    {
        delete this->channels;
    }
}
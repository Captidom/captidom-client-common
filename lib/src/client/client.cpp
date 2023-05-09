#include "client/client.h"

namespace captidom
{
    Client::Client()
    {
        this->channels = new ChannelList(nullptr, 0);
    }
    Client::Client(const UnprovisionedChannel **channels, int numChannels)
    {
        this->channels = new ChannelList(channels, numChannels);
    }

    Client::~Client()
    {
        delete this->channels;
    }

    void Client::onMessageReceived(WakeupBroadcastMessage *request, WakeupMessage **response)
    {
        *response = new WakeupMessage("platform1", "127.0.0.1");
    }
}
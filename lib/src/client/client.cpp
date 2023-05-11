#include "client/client.h"
#include "client/version.h"

namespace captidom
{
    Client::Client(const char *const platform, const char *const ip)
    {
        char *buffer = (char *)malloc(sizeof(char *) * strlen(platform + 1));
        memcpy(buffer, platform, strlen(platform) + 1);
        this->platform = buffer;

        buffer = (char *)malloc(sizeof(char *) * strlen(ip + 1));
        memcpy(buffer, ip, strlen(ip) + 1);
        this->ip = buffer;

        buffer = (char *)malloc(sizeof(char *) * strlen(CAPTIDOM_CLIENT_VERSION + 1));
        memcpy(buffer, CAPTIDOM_CLIENT_VERSION, strlen(CAPTIDOM_CLIENT_VERSION) + 1);
        this->version = buffer;

        this->channels = new ChannelList(nullptr, 0);
    }
    Client::Client(const UnprovisionedChannel **channels, int numChannels)
    {
        this->channels = new ChannelList(channels, numChannels);
    }

    Client::~Client()
    {
        free(this->version);
        free(this->ip);
        free(this->platform);
        delete this->channels;
    }

    void Client::onMessageReceived(WakeupBroadcastMessage *request, WakeupMessage **response)
    {
        *response = new WakeupMessage(this->platform, this->ip, this->version);
    }
}
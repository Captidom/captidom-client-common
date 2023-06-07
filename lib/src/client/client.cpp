#include "captidom-client-common/client/client.h"
#include "captidom-client-common/client/version.h"
#include <stdio.h>
#include "captidom-client-common/proto-v1/describe-message.h"

namespace captidom
{
    Client::Client(const char *const deviceId, const char *const platform, const char *const ip, ITransport *transport, const UnprovisionedChannel **channels, int numChannels, ChannelFactory *channelFactory) : transport(transport), channelFactory(channelFactory)
    {
        char *buffer = (char *)malloc(sizeof(char *) * strlen(deviceId + 1));
        memcpy(buffer, deviceId, strlen(deviceId) + 1);
        this->deviceId = buffer;

        buffer = (char *)malloc(sizeof(char *) * strlen(platform + 1));
        memcpy(buffer, platform, strlen(platform) + 1);
        this->platform = buffer;

        buffer = (char *)malloc(sizeof(char *) * strlen(ip + 1));
        memcpy(buffer, ip, strlen(ip) + 1);
        this->ip = buffer;

        buffer = (char *)malloc(sizeof(char *) * strlen(CAPTIDOM_CLIENT_VERSION + 1));
        memcpy(buffer, CAPTIDOM_CLIENT_VERSION, strlen(CAPTIDOM_CLIENT_VERSION) + 1);
        this->version = buffer;

        this->receiver = new Receiver(this);

        if (this->transport)
        {
            this->transport->setReceiver(this->receiver);
        }

        this->channels = new ChannelList(channels, numChannels);
    }

    Client::~Client()
    {
        free(this->deviceId);
        free(this->version);
        free(this->ip);
        free(this->platform);
        delete this->channels;
        delete this->receiver;
    }

    void Client::sendWakeup() const
    {
        WakeupMessage response(this->platform, this->ip, this->version);
        this->transport->send(&response);
    }

    void Client::sendDescribe() const
    {
        DescribeMessage response(this->deviceId, this->channels);
        this->transport->send(&response);
    }

    Client::Receiver::Receiver(Client *client) : client(client){};

    void Client::Receiver::onConnected() const
    {
        this->client->sendWakeup();
    };

    void Client::Receiver::onMessageReceived(WakeupBroadcastMessage *request) const
    {
        this->client->sendWakeup();
    };

    void Client::Receiver::onMessageReceived(DescribeRequestMessage *request) const
    {
        this->client->sendDescribe();
    };

    void Client::Receiver::onMessageReceived(ProvisionMessage *request) const
    {
        const UnprovisionedChannel *ch = this->client->channels->findById(request->getChannelId());
        if (!ch)
        {
            return;
        }

        ChannelFactory *factory = this->client->channelFactory;
        ChannelFamily family = factory->getChannelFamily(request);

        if (ChannelFamily::CHANNEL_FAMILY_IN == family)
        {
            factory->createInputChannel(request);
        }
    };
}
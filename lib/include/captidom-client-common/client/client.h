#pragma once

#include "util/list.h"
#include "channel/channel-list.h"

#include "proto-v1/wakeup-broadcast-message.h"
#include "proto-v1/wakeup-message.h"
#include "proto-v1/itransport.h"
#include "proto-v1/ireceiver.h"

namespace captidom
{

    class Client
    {
        class Receiver : public IReceiver
        {
            Client *client;

        public:
            Receiver(Client *client);
            void onMessageReceived(WakeupBroadcastMessage *request) const;
        };

        char *platform;
        char *ip;
        char *version;

        ITransport *transport;

    public:
        const Receiver *receiver;
        ChannelList *channels;

        Client(const char *const platform, const char *const ip, ITransport *transport);
        Client(const UnprovisionedChannel **channels, int numChannels);
        ~Client();

        // void onMessageReceived(DescribeRequestMessage *msg);
        // void onMessageReceived(UpgradeRequestMessage *msg);
        // void onMessageReceived(ProvisionMessage *msg);
    };
}
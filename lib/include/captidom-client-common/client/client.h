#pragma once

#include "captidom-client-common/util/list.h"
#include "captidom-client-common/channel/channel-list.h"
#include "captidom-client-common/channel/channel-factory.h"

#include "captidom-client-common/proto-v1/wakeup-broadcast-message.h"
#include "captidom-client-common/proto-v1/describe-request-message.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "captidom-client-common/proto-v1/itransport.h"
#include "captidom-client-common/proto-v1/ireceiver.h"

namespace captidom
{

    class Client
    {
        class Receiver : public IReceiver
        {
            Client *client;

        public:
            Receiver(Client *client);
            void onConnected() const;
            void onMessageReceived(WakeupBroadcastMessage *request) const;
            void onMessageReceived(DescribeRequestMessage *request) const;
            void onMessageReceived(ProvisionMessage *request) const;
        };

        char *deviceId;
        char *platform;
        char *ip;
        char *version;
        ChannelFactory *channelFactory;

        ITransport *transport;

        void sendWakeup() const;
        void sendDescribe() const;

    public:
        const Receiver *receiver;
        ChannelList *channels = 0;

        Client(const char *const deviceId, const char *const platform, const char *const ip, ITransport *transport, const UnprovisionedChannel **channels = 0, int numChannels = 0, ChannelFactory *channelFactory = 0);
        ~Client();
    };
}
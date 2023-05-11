#pragma once

#include "util/list.h"
#include "channel/channel-list.h"

#include "proto-v1/wakeup-broadcast-message.h"
#include "proto-v1/wakeup-message.h"

namespace captidom
{

    class Client
    {
        const char * platform;
        const char * ip;
        const char * version;
    public:
        ChannelList *channels;

        Client(const char * const platform, const char * const ip, const char * const version);
        Client(const UnprovisionedChannel **channels, int numChannels);
        ~Client();

        void onMessageReceived(WakeupBroadcastMessage *request, WakeupMessage **response);
        // void onMessageReceived(DescribeRequestMessage *msg);
        // void onMessageReceived(UpgradeRequestMessage *msg);
        // void onMessageReceived(ProvisionMessage *msg);

    };
}
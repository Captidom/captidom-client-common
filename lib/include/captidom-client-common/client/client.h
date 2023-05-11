#pragma once

#include "util/list.h"
#include "channel/channel-list.h"

#include "proto-v1/wakeup-broadcast-message.h"
#include "proto-v1/wakeup-message.h"

namespace captidom
{

    class Client
    {
        char * platform;
        char * ip;
        char * version;
    public:
        ChannelList *channels;

        Client(const char * const platform, const char * const ip);
        Client(const UnprovisionedChannel **channels, int numChannels);
        ~Client();

        void onMessageReceived(WakeupBroadcastMessage *request, WakeupMessage **response);
        // void onMessageReceived(DescribeRequestMessage *msg);
        // void onMessageReceived(UpgradeRequestMessage *msg);
        // void onMessageReceived(ProvisionMessage *msg);

    };
}
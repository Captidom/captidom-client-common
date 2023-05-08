#pragma once

#include "util/list.h"
#include "channel/channel-list.h"

namespace captidom
{

    class Client
    {
    public:
        ChannelList *channels;

        Client(const UnprovisionedChannel **channels, int numChannels);
        ~Client();

        // void onMessageReceived(WakeupBroadcastMessage *msg);
        // void onMessageReceived(DescribeRequestMessage *msg);
        // void onMessageReceived(UpgradeRequestMessage *msg);
        // void onMessageReceived(ProvisionMessage *msg);

    };
}
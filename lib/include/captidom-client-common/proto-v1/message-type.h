#pragma once

namespace captidom
{
    enum MessageType
    {
        WakeupMessageType,
        WakeupBroadcastMessageType,
        ByeMessageType,
        DescribeRequestMessageType,
        DescribeMessageType,
        ProvisionMessageType,
        UpdateMessageType,
        UpgradeRequestMessageType,
        LastMessageType
    };
}
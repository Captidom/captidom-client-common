#include "captidom-client-common/channel/channel-factory.h"

namespace captidom
{

    ChannelFamily ChannelFactory::getChannelFamily(const ProvisionMessage *message) const
    {

        ChannelType type = message->getChannelType();
        if (ChannelType::CHANNEL_TYPE_DIGITAL_IN == type ||
            ChannelType::CHANNEL_TYPE_ANALOG_IN == type ||
            ChannelType::CHANNEL_TYPE_DIGITAL_TEMPERATURE == type ||
            ChannelType::CHANNEL_TYPE_VCC == type ||
            ChannelType::CHANNEL_TYPE_DISTANCE == type)
        {
            return ChannelFamily::CHANNEL_FAMILY_IN;
        }

        if (ChannelType::CHANNEL_TYPE_DIGITAL_OUT == type ||
            ChannelType::CHANNEL_TYPE_ANALOG_OUT == type ||
            ChannelType::CHANNEL_TYPE_RGB_WS2811 == type)
        {
            return ChannelFamily::CHANNEL_FAMILY_OUT;
        }

        return ChannelFamily::CHANNEL_FAMILY_UNKNOWN;
    }
}
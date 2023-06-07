#pragma once
#pragma once

namespace captidom
{

    enum ChannelFamily
    {
        CHANNEL_FAMILY_IN = 0x0,
        CHANNEL_FAMILY_OUT = 0x1,
        CHANNEL_FAMILY_UNKNOWN = 0x2,
    };

    enum ChannelType
    {
        CHANNEL_TYPE_NONE = 0x0,
        CHANNEL_TYPE_DIGITAL_IN = 0x1,
        CHANNEL_TYPE_DIGITAL_OUT = 0x2,
        CHANNEL_TYPE_ANALOG_IN = 0x4,
        CHANNEL_TYPE_ANALOG_OUT = 0x8,
        CHANNEL_TYPE_DIGITAL_TEMPERATURE = 0x10,
        CHANNEL_TYPE_VCC = 0x20,
        CHANNEL_TYPE_DISTANCE = 0x40,
        CHANNEL_TYPE_RGB_WS2811 = 0x80
    };
}
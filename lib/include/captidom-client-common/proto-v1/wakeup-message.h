#pragma once

#include "proto-v1/base-message.h"

namespace captidom
{
    class WakeupMessage : BaseMessage
    {

        char *platform;
        char *ip;
        char *version;

    public:
        WakeupMessage(const char *const platform, const char *const ip, const char *const version);
        ~WakeupMessage();

        const char *const getPlatform();
        const char *const getIp();
        const char *const getVersion();
    };
}
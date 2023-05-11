#include "proto-v1/wakeup-message.h"
#include "client/version.h"
#include <cstdlib>
#include <cstring>

namespace captidom
{
    WakeupMessage::WakeupMessage(const char *const platform, const char *const ip, const char *const version) : BaseMessage(MessageType::WakeupMessageType)
    {
        this->platform = (char *)malloc(sizeof(char *) * strlen(platform + 1));
        memcpy(this->platform, platform, strlen(platform) + 1);

        this->ip = (char *)malloc(sizeof(char *) * strlen(ip + 1));
        memcpy(this->ip, ip, strlen(ip) + 1);

        this->version = (char *)malloc(sizeof(char *) * strlen(version + 1));
        memcpy(this->version, version, strlen(version) + 1);
    };

    WakeupMessage::~WakeupMessage()
    {
    }

    const char *const WakeupMessage::getPlatform()
    {
        return this->platform;
    }

    const char *const WakeupMessage::getIp()
    {
        return this->ip;
    }

    const char *const WakeupMessage::getVersion()
    {
        return this->version;
    }
}
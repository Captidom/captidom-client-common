#include <stdlib.h>

#include "captidom-channel-common/list.h"
#include "captidom-channel-common/poll-channel.hpp"

namespace
{
    const captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN, captidom::ChannelType::CHANNEL_TYPE_DIGITAL_TEMPERATURE};
}

class SimpleCountPollChannel : public captidom::PollChannel<int>
{
private:
    int currentCount;

public:
    SimpleCountPollChannel(int currentCount, int id, const char *name, int nameLength) : PollChannel<int>(id, name, nameLength, types, 2)
    {
        this->currentCount = currentCount;
    };

    void produceValue(int *newValue)
    {
        *newValue = this->currentCount++;
    }

    void serializeValue(int *rawValue, captidom::List<char> **serializedValue)
    {
        if (*serializedValue)
        {
            delete *serializedValue;
        }

        char buffer[16];
        sprintf(buffer, "%d", *rawValue);
        *serializedValue = new captidom::List<char>(buffer, strlen(buffer));
    }
};

int main(int argc, char *argv[])
{
    SimpleCountPollChannel ch = SimpleCountPollChannel(10, 0, "test", 4);

    const char *buffer;
    int nameLen;
    ch.getName(&buffer, nameLen);
    printf("Name: %s\n", buffer);
    ch.getValue(&buffer, nameLen);
    printf("Value: %s\n", buffer);
    ch.getValue(&buffer, nameLen);
    printf("Value: %s\n", buffer);
    ch.getValue(&buffer, nameLen);
    printf("Value: %s\n", buffer);

    const captidom::ChannelType *types;
    int typesLen;
    ch.getSupportedTypes(&types, typesLen);
    printf("Types: %d (%d)\n", typesLen, types[0]);

    captidom::PollChannelConfig originalConfig = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN, captidom::ChannelMode::CHANNEL_MODE_POLL};

    ch.setConfig(&originalConfig);

    {
        const captidom::PollChannelConfig config = ch.getConfig();

        printf("Configured type: %d; mode %d\n", config.type, config.mode);
    }

    originalConfig.type = captidom::ChannelType::CHANNEL_TYPE_DIGITAL_TEMPERATURE;
    originalConfig.mode = captidom::ChannelMode::CHANNEL_MODE_PUSH;

    ch.setConfig(&originalConfig);
    {
        const captidom::PollChannelConfig config = ch.getConfig();

        printf("Reconfigured type: %d; mode %d\n", config.type, config.mode);
    }

    originalConfig.type = captidom::ChannelType::CHANNEL_TYPE_NONE;
    originalConfig.mode = captidom::ChannelMode::CHANNEL_MODE_NONE;

    ch.setConfig(&originalConfig);
    {
        const captidom::PollChannelConfig config = ch.getConfig();

        printf("Disabled type: %d; mode %d\n", config.type, config.mode);
    }
    return 0;
}
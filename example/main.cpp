#include <stdlib.h>

#include "captidom-channel-common/list.h"
#include "captidom-channel-common/poll-channel.h"

namespace
{
    const captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN, captidom::ChannelType::CHANNEL_TYPE_DIGITAL_TEMPERATURE};
    const captidom::ChannelMode pollModes[] = {captidom::ChannelMode::CHANNEL_MODE_POLL};
}

class SimpleCountPollChannel : virtual public captidom::PollChannel
{
protected:
    void applyConfig(const captidom::ChannelConfig *config)
    {
    }

private:
    int currentCount;

public:
    SimpleCountPollChannel(int currentCount, int id, const char *name, int nameLength) : BaseChannel(id, name, nameLength, types, 2, pollModes, 1), PushChannel(&captidom::EMPTY_CHANNEL_VALUE_CALLBACK)
    {
        this->currentCount = currentCount;
    };

    void produceValue(char *value)
    {
        sprintf(value, "%d", this->currentCount++);
    }
};

int main(int argc, char *argv[])
{
    SimpleCountPollChannel ch = SimpleCountPollChannel(10, 0, "test", 4);

    const char *buffer;
    int nameLen;

    ch.getName(&buffer, nameLen);
    printf("Name: %s\n", buffer);
    printf("Value: %s\n", ch.getValue());
    printf("Value: %s\n", ch.getValue());
    printf("Value: %s\n", ch.getValue());

    const captidom::ChannelType *types;
    int typesLen;
    ch.getSupportedTypes(&types, typesLen);
    printf("Types: %d (%d)\n", typesLen, types[0]);

    captidom::ChannelConfig originalConfig = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN, captidom::ChannelMode::CHANNEL_MODE_POLL};

    ch.setConfig(&originalConfig);

    {
        const captidom::ChannelConfig *config = ch.getConfig();

        printf("Configured type: %d; mode %d\n", config->type, config->mode);
    }

    originalConfig.type = captidom::ChannelType::CHANNEL_TYPE_DIGITAL_TEMPERATURE;
    originalConfig.mode = captidom::ChannelMode::CHANNEL_MODE_PUSH;

    ch.setConfig(&originalConfig);
    {
        const captidom::ChannelConfig *config = ch.getConfig();

        printf("Reconfigured type: %d; mode %d\n", config->type, config->mode);
    }

    originalConfig.type = captidom::ChannelType::CHANNEL_TYPE_NONE;
    originalConfig.mode = captidom::ChannelMode::CHANNEL_MODE_NONE;

    ch.setConfig(&originalConfig);
    {
        const captidom::ChannelConfig *config = ch.getConfig();

        printf("Disabled type: %d; mode %d\n", config->type, config->mode);
    }
    return 0;
}
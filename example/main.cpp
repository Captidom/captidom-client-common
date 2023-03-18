#include <stdlib.h>

#include "captidom-client-common/list.h"
#include "captidom-client-common/unprovisioned-channel.h"
#include "captidom-client-common/poll-channel.h"

namespace
{
    const captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN, captidom::ChannelType::CHANNEL_TYPE_DIGITAL_TEMPERATURE};
    const captidom::ChannelMode pollModes[] = {captidom::ChannelMode::CHANNEL_MODE_POLL};
}

captidom::UnprovisionedChannel *unprovisionedCountChannel = new captidom::UnprovisionedChannel(0, "test", 4, types, 2, pollModes, 1);

class SimpleCountPollChannel : virtual public captidom::PollChannel
{
private:
    int currentCount;

public:
    SimpleCountPollChannel(int currentCount, int id, const char *name, int nameLength) : BaseChannel(id, name, nameLength)
    {
        this->currentCount = currentCount;
    };

    void produceValue(char *value)
    {
        sprintf(value, "%d", this->currentCount++);
    }

    captidom::ChannelType getType() {
        return captidom::ChannelType::CHANNEL_TYPE_ANALOG_OUT;
    }

    captidom::ChannelMode getMode() {
        return captidom::ChannelMode::CHANNEL_MODE_POLL;
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
    unprovisionedCountChannel->getSupportedTypes(&types, typesLen);
    printf("Types: %d (%d)\n", typesLen, types[0]);

    printf("Channel type: %d; mode %d\n", ch.getType(), ch.getMode());

    return 0;
}
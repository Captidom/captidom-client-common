#include <stdlib.h>

#include "captidom-client-common/list.h"
#include "captidom-client-common/unprovisioned-channel.h"
#include "captidom-client-common/poll-channel.h"

namespace
{
    captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_IN};
    captidom::ChannelMode pollModes[] = {captidom::ChannelMode::CHANNEL_MODE_POLL};
}

captidom::UnprovisionedChannel *unprovisionedCountChannel = new captidom::UnprovisionedChannel(0, "test", 4, types, 1, pollModes, 1);

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

    captidom::ChannelType getType()
    {
        return captidom::ChannelType::CHANNEL_TYPE_ANALOG_OUT;
    }

    captidom::ChannelMode getMode()
    {
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

    auto typesList = unprovisionedCountChannel->getSupportedTypes();
    captidom::ChannelType *types = (captidom::ChannelType *)malloc(10 * sizeof(captidom::ChannelType));

    typesList->getItems(&types);

    printf("Types: %d (%d, %d, %d)\n", typesList->getCount(), types[0], types[1], types[2]);

    free(types);

    printf("Channel type: %d; mode %d\n", ch.getType(), ch.getMode());

    return 0;
}
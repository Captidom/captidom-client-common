#include <stdlib.h>

#include "captidom-channel-common/list.h"
#include "captidom-channel-common/poll-channel.h"

namespace {
    static const captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_OUT};
}

class SimpleCountPollChannel : public captidom::PollChannel
{
private:
    int currentCount;

public:
    SimpleCountPollChannel(int currentCount, int id, const char *name, int nameLength) : PollChannel(id, name, nameLength, types, 1)
    {
        this->currentCount = currentCount;
    };

    void getValue(const char **strValue, int &strValueLen)
    {
        char buffer[16];
        sprintf(buffer, "%d", this->currentCount);

        delete this->value;
        this->value = new captidom::List<char>(buffer, strlen(buffer));

        PollChannel::getValue(strValue, strValueLen);

        this->currentCount++;
    };
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

    return 0;
}
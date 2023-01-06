#include <stdlib.h>

#include "captidom-channel-common/list.h"
#include "captidom-channel-common/input-channel.hpp"

namespace {
    const captidom::ChannelType types[] = {captidom::ChannelType::CHANNEL_TYPE_ANALOG_OUT};
    const captidom::ChannelMode modes[] = {captidom::ChannelMode::CHANNEL_MODE_POLL};
}

class SimpleCountPollChannel : public captidom::InputChannel<int>
{
private:
    int currentCount;

public:


    SimpleCountPollChannel(int currentCount, int id, const char *name, int nameLength) : InputChannel<int>(id, name, nameLength, types, 1, modes, 1)
    {
        this->currentCount = currentCount;
    };

    void produceValue(int **newValue) {
        if (*newValue) {
            delete *newValue;
        }

        *newValue = new int(this->currentCount++);
    }

    void serializeValue(int *rawValue, captidom::List<char> **serializedValue) {
        if (*serializedValue) {
            delete *serializedValue;
        }

        char buffer[16];
        sprintf(buffer, "%d", this->currentCount);
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

    return 0;
}
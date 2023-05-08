#include "channel/input-channel.h"

namespace captidom
{
    const char * InputChannel::getValue()
    {
        this->produceValue(this->serializedValue);
        return this->serializedValue;
    }
}
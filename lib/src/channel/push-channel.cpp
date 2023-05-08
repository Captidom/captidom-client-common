#include "channel/push-channel.h"

namespace captidom
{
    PushChannel::PushChannel(ChannelValueCallback *newValueCB)
    {
        this->newValueCB = new ChannelValueCallback();
        if (newValueCB) {
            *this->newValueCB = *newValueCB;
        }
    }

    PushChannel::~PushChannel() {
        delete this->newValueCB;
    }

    const char * PushChannel::getValue() {
        char buffer[64];
        this->produceValue(buffer);
        bool hasNewValue = strcmp(buffer, this->serializedValue);

        strcpy(this->serializedValue, buffer);

        if (hasNewValue && this->newValueCB->callback) {
            this->newValueCB->callback(this->newValueCB->context, this->serializedValue, this->getId());
        }

        return this->serializedValue;
    }
}
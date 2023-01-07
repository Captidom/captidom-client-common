#include "push-channel.h"

namespace captidom
{
    PushChannel::PushChannel(ChannelValueCallback *newValueCB)
    {
        this->newValueCB = new ChannelValueCallback();
        *this->newValueCB = *newValueCB;
    }
    PushChannel::~PushChannel() {
        delete this->newValueCB;
    }
}
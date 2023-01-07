#include "push-channel.h"

namespace captidom
{
    PushChannel::PushChannel(ChannelValueCallback *newValueCB)
    {
        this->newValueCB = newValueCB;
    }
}
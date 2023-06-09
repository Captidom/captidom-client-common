#pragma once

#include "captidom-client-common/channel/base-channel.h"
#include "captidom-client-common/channel/base-provisioned-channel.h"

namespace captidom
{
    class InputChannel : virtual public BaseChannel, virtual public BaseProvisionedChannel
    {
    protected:
        char serializedValue[64];

        virtual void produceValue(char *serializedValue) = 0;

    public:
        InputChannel() {};
        virtual const char * getValue();
    };
}
#pragma once

#include "captidom-client-common/proto-v1/base-message.h"

namespace captidom
{
    class ProvisionMessage : BaseMessage
    {
    public:
        ProvisionMessage();
        ~ProvisionMessage();
    };
}
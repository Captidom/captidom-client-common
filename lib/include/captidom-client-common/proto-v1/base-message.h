#pragma once

#include "captidom-client-common/proto-v1/message-type.h"

namespace captidom
{

    class BaseMessage
    {
    private:
        MessageType type;

    protected:
        BaseMessage(MessageType type) : type(type){};

    public:
        MessageType getType() { return this->type; };
    };
}
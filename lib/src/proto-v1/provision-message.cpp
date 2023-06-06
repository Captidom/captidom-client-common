#include "captidom-client-common/proto-v1/provision-message.h"
#include "captidom-client-common/client/version.h"
#include <cstdlib>
#include <cstring>

namespace captidom
{
    ProvisionMessage::ProvisionMessage() : BaseMessage(MessageType::ProvisionMessageType)
    {
    };

    ProvisionMessage::~ProvisionMessage()
    {
    }
}
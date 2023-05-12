#include "proto-v1/itransport.h"

namespace captidom
{
    void ITransport::setReceiver(const IReceiver *receiver)
    {
        this->receiver = receiver;
    }
}
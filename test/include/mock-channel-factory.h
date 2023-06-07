#pragma once

#include "captidom-client-common/client/client.h"
#include "gmock/gmock.h"

namespace captidom
{
    class MockChannelFactory : public ChannelFactory
    {
    public:
        MOCK_METHOD(ChannelFamily, getChannelFamily, (const ProvisionMessage *message), (const override));
        MOCK_METHOD(InputChannel*, createInputChannel, (const ProvisionMessage *message), (const override));
        MOCK_METHOD(OutputChannel*, createOutputChannel, (const ProvisionMessage *message), (const override));
    };
}
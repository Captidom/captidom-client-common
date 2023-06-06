#pragma once

#include "captidom-client-common/client/client.h"
#include "gmock/gmock.h"

namespace captidom
{
    class MockTransport : public ITransport
    {
    public:
        MOCK_METHOD(void, start, (), (override));
        MOCK_METHOD(void, stop, (), (override));
        MOCK_METHOD(void, send, (const WakeupBroadcastMessage *message), (const override));
        MOCK_METHOD(void, send, (const WakeupMessage *message), (const override));
        MOCK_METHOD(void, send, (const DescribeMessage *message), (const override));

        void connect()
        {
            this->receiver->onConnected();
        }

        void receiveWakeupBroadcast()
        {
            WakeupBroadcastMessage request;
            this->receiver->onMessageReceived(&request);
        }

        void receiveDescribeRequest()
        {
            DescribeRequestMessage request;
            this->receiver->onMessageReceived(&request);
        }
    };
}
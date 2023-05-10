#include "captidom-client-common/client/client.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "gtest/gtest.h"

using namespace captidom;

TEST(client, onWakeupMessageBroadcast)
{
    Client *client = new Client();
    WakeupMessage *message = (WakeupMessage *)malloc(sizeof(WakeupMessage));
    client->onMessageReceived(nullptr, &message);
    ASSERT_STREQ(message->getPlatform(), "platform1");
    ASSERT_STREQ(message->getIp(), "127.0.0.1");
    ASSERT_STREQ(message->getVersion(), "0.0.0");
    free(message);
}
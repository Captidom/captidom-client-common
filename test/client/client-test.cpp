#include "captidom-client-common/client/client.h"
#include "captidom-client-common/proto-v1/wakeup-message.h"
#include "client/version.h"
#include "gtest/gtest.h"

using namespace captidom;

TEST(client, onWakeupMessageBroadcast)
{
    const char *platform = "some-test-platform";
    const char *ip = "127.0.0.1";

    Client *client = new Client(platform, ip);
    WakeupMessage *message = (WakeupMessage *)malloc(sizeof(WakeupMessage));
    client->onMessageReceived(nullptr, &message);
    ASSERT_STREQ(message->getPlatform(), platform);
    ASSERT_STREQ(message->getIp(), ip);
    ASSERT_STREQ(message->getVersion(), CAPTIDOM_CLIENT_VERSION);
    free(message);
}
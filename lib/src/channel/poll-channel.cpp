#include "captidom-client-common/channel/poll-channel.h"

namespace captidom
{
    PollChannel::PollChannel() {};

    void PollChannel::setPollingInterval(int pollInterval) {
        this->pollIntervalSeconds = pollInterval;
    }
    int PollChannel::getPollingInterval() {
        return this->pollIntervalSeconds;
    }
}
#include "poll-channel.h"

namespace captidom
{
    PollChannel::PollChannel() {};

    void PollChannel::setPollingInterval(int pollInterval) {
        this->pollIntervalSeconds = pollInterval;
    }
}
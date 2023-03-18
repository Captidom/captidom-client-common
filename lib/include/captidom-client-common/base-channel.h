#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include <string.h>

#include "list.h"
#include "channel-config.h"

namespace captidom
{

    class BaseChannel
    {
    private:
        int id;

        const char *name;
        int nameLength;

    public:
        BaseChannel(int id, const char *name, int nameLength);

        ~BaseChannel();

        void getName(const char **destination, int &length) const;

        int getId() const;
    };
}
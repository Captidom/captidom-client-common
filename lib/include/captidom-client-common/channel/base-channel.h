#pragma once

#include <string.h>

#include "captidom-client-common/util/list.h"
#include "captidom-client-common/channel/channel-config.h"

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
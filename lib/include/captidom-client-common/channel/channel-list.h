#pragma once

#include "util/list.h"
#include "unprovisioned-channel.h"

namespace captidom
{

    class ChannelList : public List<const UnprovisionedChannel *>
    {
    public:
        ChannelList(const UnprovisionedChannel **items, int count) : List(items, count) {}

        const UnprovisionedChannel *findById(int id)
        {
            if (!this->firstItem)
            {
                return 0;
            }

            auto item = this->firstItem;
            while (item)
            {
                if ((*item->payload)->getId() == id)
                {
                    return *item->payload;
                }

                item = item->next;
            }

            return 0;
        }
    };

}
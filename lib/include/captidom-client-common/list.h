#pragma once

#include <cstring>

namespace captidom
{

    template <class T>
    class List
    {
    private:
        T *items;
        int count;

    public:
        List(const T *items, int count)
        {
            this->count = count;
            this->items = (T *)malloc(count * sizeof(T));
            memcpy(this->items, items, count * sizeof(T));
        }

        ~List()
        {
            free(this->items);
        }

        void getItems(const T **destination, int &count)
        {
            *destination = this->items;
            count = this->count;
        }
    };
}
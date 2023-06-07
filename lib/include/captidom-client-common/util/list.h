#pragma once

#include <stdlib.h>

namespace captidom
{

    template <class T>
    class List
    {
    protected:
        template <class P>
        class ListItem
        {
        public:
            P *payload;
            ListItem<P> *next;
            ListItem<P> *prev;
        };

        ListItem<T> *firstItem = 0;

        ListItem<T> *getLastItem()
        {
            auto item = this->firstItem;

            while (item && item->next)
            {
                item = item->next;
            }

            return item;
        }

        void clear()
        {
            auto itemToDelete = this->firstItem;
            while (itemToDelete)
            {
                auto next = itemToDelete->next;
                delete itemToDelete;

                itemToDelete = next;
            }
        }

    public:
        List(T *items, int count)
        {
            for (int i = 0; i < count; i++)
            {
                this->add(&(items[i]));
            }
        }

        void add(T *item)
        {
            auto itemToAdd = new ListItem<T>();

            itemToAdd->next = 0;
            itemToAdd->prev = 0;
            itemToAdd->payload = item;

            if (0 == this->firstItem)
            {
                this->firstItem = itemToAdd;
                return;
            }

            auto lastItem = this->getLastItem();

            lastItem->next = itemToAdd;
            itemToAdd->prev = lastItem;
        }

        bool contains(const T *itemToSearch) const
        {
            auto item = this->firstItem;

            while (item)
            {
                if (*item->payload == *itemToSearch)
                    return true;

                item = item->next;
            }

            return false;
        }

        ~List()
        {
            this->clear();
        }

        void getItems(T **destination) const
        {
            auto item = this->firstItem;

            int currentIndex = 0;
            while (item)
            {
                (*destination)[currentIndex] = *item->payload;
                item = item->next;
            }
        }

        T const *getItem(unsigned int index) const
        {
            if (index >= this->getCount() || 0 == this->firstItem)
            {
                return 0;
            }

            auto item = this->firstItem;

            while (item && index)
            {
                item = item->next;
                index--;
            }

            return item->payload;
        }

        int getCount() const
        {
            if (0 == this->firstItem)
            {
                return 0;
            }

            int count = 1;
            auto item = this->firstItem;

            while (item = item->next)
            {
                count++;
            }

            return count;
        }
    };
}
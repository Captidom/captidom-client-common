#pragma once

#include "input-channel.h"

namespace captidom
{
    template <class T_DATA_TYPE>
    InputChannel<T_DATA_TYPE>::InputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedModes, int maxModes) : Channel(id, name, nameLength, supportedTypes, maxTypes, supportedModes, maxModes)
    {
        this->serializedValue = new List<char>("", 0);
    }

    template <class T_DATA_TYPE>
    InputChannel<T_DATA_TYPE>::~InputChannel()
    {
        delete this->serializedValue;
    }

    template <class T_DATA_TYPE>
    void InputChannel<T_DATA_TYPE>::_produceAndSerializeValue()
    {
        this->produceValue(&this->rawValue);
        this->serializeValue(this->rawValue, &this->serializedValue);
    }

    template <class T_DATA_TYPE>
    void InputChannel<T_DATA_TYPE>::getValue(const char **value, int &valueLen)
    {
        this->_produceAndSerializeValue();
        this->serializedValue->getItems(value, valueLen);
    }
}
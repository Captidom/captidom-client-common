#pragma once

#include "input-channel.h"

namespace captidom
{
    IInputChannel::IInputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedModes, int maxModes) : Channel(id, name, nameLength, supportedTypes, maxTypes, supportedModes, maxModes)
    {
        this->serializedValue = new List<char>("", 0);
    }

    IInputChannel::~IInputChannel()
    {
        delete this->serializedValue;
    }

    void IInputChannel::getValue(const char **value, int &valueLen)
    {
        this->_produceAndSerializeValue();
        this->serializedValue->getItems(value, valueLen);
    }

    template <class T_DATA_TYPE>
    InputChannel<T_DATA_TYPE>::InputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedModes, int maxModes) : IInputChannel(id, name, nameLength, supportedTypes, maxTypes, supportedModes, maxModes)
    {
    }

    template <class T_DATA_TYPE>
    void InputChannel<T_DATA_TYPE>::_produceAndSerializeValue()
    {
        if (this->rawValue)
        {
            delete this->rawValue;
        }
        this->rawValue = new T_DATA_TYPE();
        this->produceValue(this->rawValue);
        this->serializeValue(this->rawValue, &this->serializedValue);
    }
}
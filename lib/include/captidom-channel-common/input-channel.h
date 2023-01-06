#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "channel.h"

namespace captidom
{

    class IInputChannel : public Channel
    {
    private:
        virtual void _produceAndSerializeValue() = 0;

    protected:
        List<char> *serializedValue = 0;

    public:
        IInputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedmodes, int maxModes);
        ~IInputChannel();
        void getValue(const char **strValue, int &strValueLen);
    };

    template <class T_DATA_TYPE>
    class InputChannel : public IInputChannel
    {
    private:
        void _produceAndSerializeValue();

    protected:
        T_DATA_TYPE *rawValue = 0;

        virtual void produceValue(T_DATA_TYPE *rawValue) = 0;
        virtual void serializeValue(T_DATA_TYPE *rawValue, List<char> **serializedValue) = 0;

    public:
        InputChannel(int id, const char *name, int nameLength, const ChannelType *supportedTypes, int maxTypes, const ChannelMode *supportedmodes, int maxModes);
    };
}

#include "input-channel.hpp"
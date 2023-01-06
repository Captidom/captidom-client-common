#pragma once

#include <functional>
#include <chrono>
#include <thread>

#include "input-channel.h"

namespace captidom
{

    template<class T_DATA_TYPE>
    class OutputChannel : public InputChannel<T_DATA_TYPE>
    {
    public:
        virtual void setValue(const char *strValue, int strValueLen) = 0;
    };
}
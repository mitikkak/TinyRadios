
#pragma once

#include <string>

class TinyDebugSerial
{
    std::string buffer;
public:
    TinyDebugSerial()
        : buffer()
    {}
    void print(const char* const)
    {

    }
    void print(const unsigned int)
    {

    }

    void println(const char* const)
    {

    }
    void println(const unsigned int)
    {

    }
    std::string getPrints() const
    {
        return buffer;
    }
};


#pragma once

#include <string>

class TinyDebugSerial
{
    std::string buffer;
public:
    TinyDebugSerial()
        : buffer()
    {}
    void print(const char* const s)
    {
        buffer += s;
    }
    void print(const unsigned int v)
    {
        buffer += std::to_string(v);
    }

    void println(const char* const s)
    {
        print(s);
    }
    void println(const unsigned int v)
    {
        print(v);
    }
    std::string getPrints() const
    {
        return buffer;
    }
};

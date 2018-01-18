
#pragma once

#include <string>

static constexpr unsigned HEX = 0;

class TinyDebugSerial
{
    std::string buffer;
public:
    TinyDebugSerial()
        : buffer()
    {}
    void print(const char* const s, const int format = HEX)
    {
        buffer += s;
    }
    void print(const unsigned int v, const int format = HEX)
    {
        buffer += std::to_string(v);
    }

    void println(const char* const s, const int format = HEX)
    {
        print(s);
    }
    void println(const unsigned int v, const int format = HEX)
    {
        print(v);
    }
    std::string getPrints() const
    {
        return buffer;
    }
};

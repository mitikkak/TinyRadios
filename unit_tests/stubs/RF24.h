
#pragma once

#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
class RF24
{
    bool started;
    bool stopped;
    bool givePing;
    uint8_t* writeBuffer;
public:
    RF24(int, int)
        : started(false), stopped(false), givePing(false), writeBuffer(0)
    {}
    ~RF24()
    {
        delete[] writeBuffer;
    }
    void startListening()
    {
        started = true;
    }
    void stopListening()
    {
        stopped = true;
    }
    bool stoppedListening() const
    {
        return stopped;
    }
    bool startedListening() const
    {
        return started;
    }
    bool available() const
    {
        return true;
    }
    void read(void* handle, unsigned const size) const;

    bool write( const void* buf, uint8_t len )
    {
        if (!stoppedListening())
        {
            printf(" ERROR: RF24 write called before stopListening!\n");
        }
        writeBuffer = new uint8_t[len];
        memcpy(static_cast<void*>(writeBuffer), buf, len);
        return true;
    }
    const uint8_t* written() const
    {
        return writeBuffer;
    }
    void ping(bool const val)
    {
        givePing = val;
    }
    void openWritingPipe(const uint8_t* address)
    {

    }

};

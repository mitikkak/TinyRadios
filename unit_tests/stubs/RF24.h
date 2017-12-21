
#pragma once

#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
class RF24
{
    bool startedListening;
    bool stoppedListening;
    bool givePing;
    uint8_t* writeBuffer;
public:
    RF24(int, int)
        : startedListening(false), stoppedListening(false), givePing(false), writeBuffer(0)
    {}
    ~RF24()
    {
        delete[] writeBuffer;
    }
    void startListening()
    {
        startedListening = true;
    }
    void stopListening()
    {
        stoppedListening = true;
    }
    bool available() const
    {
        return true;
    }
    void read(void* handle, unsigned const size) const;

    bool write( const void* buf, uint8_t len )
    {
        if (!stoppedListening)
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

};


#pragma once

#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
class RF24
{
    bool stoppedListening;
    uint8_t* writeBuffer;
public:
    RF24()
        : stoppedListening(false), writeBuffer(0)
    {}
    ~RF24()
    {
        delete[] writeBuffer;
    }

    void stopListening()
    {
        stoppedListening = true;
    }
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
    uint8_t* written()
    {
        return writeBuffer;
    }

};

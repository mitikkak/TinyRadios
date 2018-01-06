
#pragma once

#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
class RF24
{
    bool started;
    bool stopped;
    int msgId;
    int transactionId;
    uint8_t* writeBuffer;
public:
    RF24(int, int)
        : started(false), stopped(false), msgId(0), transactionId(0), writeBuffer(0)
    {}
    ~RF24()
    {
        delete[] writeBuffer;
    }
    typedef void (*ReadFunctionType)(void* handle, unsigned const size);
    static ReadFunctionType readFunctionPtr;

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
    void setMsgId(int const val)
    {
        msgId = val;
    }
    void setTransactionId(int const val)
    {
        transactionId = val;
    }
    void openWritingPipe(const uint8_t* address)
    {

    }

};

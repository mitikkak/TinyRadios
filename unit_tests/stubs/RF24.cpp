
#include "RF24.h"
#include "shared/Messages.h"

RF24::ReadFunctionType RF24::readFunctionPtr;
void RF24::read(void* handle, unsigned const size) const
{
    if (readFunctionPtr)
    {
        return readFunctionPtr(handle, size);
    }
    Ping* req = static_cast<Ping*>(handle);
    req->header.msgId = msgId;
    req->header.transactionId = transactionId;
}

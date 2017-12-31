
#include "RF24.h"
#include "shared/Messages.h"

void RF24::read(void* handle, unsigned const size) const
{
    Ping* req = static_cast<Ping*>(handle);
    req->header.msgId = msgId;
    req->header.transactionId = transactionId;
}


#include "RF24.h"
#include "shared/Messages.h"

void RF24::read(void* handle, unsigned const size) const
{
    if (givePing)
    {
        Ping* req = static_cast<Ping*>(handle);
        req->header.msgId = PING_REQUEST;
    }
}

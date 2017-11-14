
#include "Messages.h"

void sendPingResponse(Ping const&  req, RF24& radio)
{
  radio.stopListening();
  Ping resp(PING_RESPONSE, req.header.transactionId);
  radio.write( &resp, sizeof(resp) );
}


#include "Arduino.h"
#include "Components.h"
#include "Messages.h"
#include "Loop.h"

void sendPingRequest(unsigned int const rounds)
{
  radio.stopListening();
  Ping request(PING_REQUEST, rounds);
  radio.write( &request, sizeof(request) );
}

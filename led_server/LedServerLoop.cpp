
#include "Arduino.h"
#include "Components.h"
#include "shared/Messages.h"
#include "Loop.h"

void sendPingRequest(unsigned int const rounds)
{
  radio.stopListening();
  Ping request(PING_REQUEST, rounds);
  radio.write( &request, sizeof(request) );
}
bool getPingResponse(Ping& resp)
{
  radio.startListening();
  if (radio.available() )
  {
    radio.read( &resp, sizeof(resp) );
    if (resp.header.msgId == PING_RESPONSE)
    {
        return true;
    }
  }
  return false;
}
uint8_t remote_address[3][5] = {
  {0xAA, 0xBB, 0xCC, 0xDD, 0x1},
  {0xAA, 0xBB, 0xCC, 0xDD, 0x2},
  {0xAA, 0xBB, 0xCC, 0xDD, 0x3}
};
bool onePingRound(RadioMode& mode, unsigned int const receiver, unsigned int const transactionId, TIME& timeSpent, unsigned int& attempts)
{
    radio.openWritingPipe(remote_address[receiver]);
    TIME timeNow = millis();
    TIME const startTime = timeNow;
    mode.start(RadioMode::sending, timeNow);
    while(!mode.swap(timeNow, false))
    {
        sendPingRequest(transactionId);
        timeNow = millis();
    }
    bool respReceived = false;
    Ping resp(0,0);
    while(!mode.swap(timeNow, respReceived))
    {
        respReceived = getPingResponse(resp);
        timeNow = millis();
    }
    timeSpent = millis() - startTime;
    return (resp.header.msgId == PING_RESPONSE) && (resp.header.transactionId == transactionId);
}

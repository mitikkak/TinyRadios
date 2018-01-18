
#include "Arduino.h"
#include "Components.h"
#include "shared/Messages.h"
#include "Loop.h"

void sendLedRequest(unsigned int const transactionId, int const msgId)
{
  radio.stopListening();
  LedRequest request(msgId, transactionId);
  _SERIAL.println(request.get(), HEX);
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
bool onePingRound(RadioMode& mode, unsigned int const receiver, unsigned int const transactionId, TIME& timeSpent, unsigned int& respTrId, int const msgId)
{
    //_SERIAL.println("onePingRound");
    radio.openWritingPipe(remote_address[receiver]);
    TIME timeNow = millis();
    TIME const startTime = timeNow;
    mode.start(RadioMode::sending, timeNow);
    int numSent = 0;
    while(!mode.swap(timeNow, false))
    {
        sendLedRequest(transactionId, msgId);
        timeNow = millis();
        numSent++;
    }
    //_SERIAL.println(numSent);
    bool respReceived = false;
    Ping resp(0,-1);
    while(!mode.swap(timeNow, respReceived))
    {
        /*respReceived =*/ getPingResponse(resp);
        timeNow = millis();
    }
    timeSpent = millis() - startTime;
    respTrId = resp.header.transactionId;
    return (resp.header.msgId == PING_RESPONSE) /*&& (resp.header.transactionId == transactionId)*/;
}


#include "Arduino.h"
#include "Components.h"
#include "shared/Messages.h"
#include "Loop.h"
#include "shared/Addresses.h"

void sendLedRequest(unsigned int const transactionId, int const msgId)
{
  LedRequest request(msgId, transactionId);
  _SERIAL.println(request.get(), HEX);
  radio.write( &request, sizeof(request) );
}
bool getPingResponse(Ping& resp)
{
  bool retValue = false;
  if (radio.available() )
  {
    radio.read( &resp, sizeof(resp) );
    if (resp.header.msgId == PING_RESPONSE)
    {
        retValue = true;
    }
  }
  return retValue;
}
bool onePingRound(RadioMode& mode, unsigned int const receiver, unsigned int const transactionId, TIME& timeSpent, unsigned int& respTrId, int const msgId)
{
    //_SERIAL.println("onePingRound");
    radio.stopListening();
    radio.openWritingPipe(led_node_addresses[receiver]);
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
    const int pipe = 0;
    radio.openReadingPipe(pipe, led_server_addresses[receiver]);
    radio.startListening();
    //_SERIAL.println(numSent);
    bool respReceived = false;
    Ping resp(0,-1);
    while(!mode.swap(timeNow, respReceived))
    {
        /*respReceived =*/ getPingResponse(resp);
        timeNow = millis();
    }
    radio.closeReadingPipe(pipe);
    timeSpent = millis() - startTime;
    respTrId = resp.header.transactionId;
    _SERIAL.print("resp: ");_SERIAL.print(resp.header.msgId);
    _SERIAL.print("timeSpent: ");_SERIAL.print(timeSpent);
    return (resp.header.msgId == PING_RESPONSE) /*&& (resp.header.transactionId == transactionId)*/;
}

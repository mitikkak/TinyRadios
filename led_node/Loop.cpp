
#include "led_node/Loop.h"
#include "led_node/Components.h"

#ifndef NODE_ALWAYS_ON
int transactionId = 0;
void loop() {
    TIME const timeNow = millis();
    if (RadioMode::listening == mode.state())
    {
        transactionId = ledNodeLoopIf(mode, timeNow, _SERIAL);
    }
    else
    {
        //digitalWrite(sendIndicator, HIGH);
        ledNodeLoopElse(radio, mode, transactionId, timeNow, _SERIAL);
    }
}
#else
void loop() {

}
#endif

void ledNodeLoop()
{

}
void ledNodeLoopElse(RF24& radio, RadioMode& mode, const int transactionId, TIME const timeNow, TinyDebugSerial& _SERIAL)
{
    if (mode.swap(timeNow, false))
    {
        _SERIAL.println("end of sending period");
        return;
    }
    const Ping resp(PING_RESPONSE, transactionId);
    sendPingResponse(resp, radio);
}
void sendPingResponse(Ping const&  resp, RF24& radio)
{
  radio.stopListening();
  //Ping resp(PING_RESPONSE, req.header.transactionId);
  radio.write( &resp, sizeof(resp) );
}
LedRequest getLedRequest()
{
  radio.startListening();
  LedRequest req(0);
  if (radio.available())
  {
    radio.read( &req, sizeof(req) );
  }
  return req;
}
int ledNodeLoopIf(RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL)
{
    LedRequest const req = getLedRequest();
    bool reqReceived = false;
    if (req.header.msgId == LED_REQUEST)
    {
//      if (!connectionEstablished)
//      {
//          //blinker.begin(timeNow);
//      }
      //blinker.update(timeNow);
//      connectionEstablished = true;
      const int ledState = (req.led == Led_OFF) ? LOW : HIGH;
      digitalWrite(ledPin, ledState);
      reqReceived = true;
    }
    if (mode.swap(timeNow, reqReceived))
    {
        _SERIAL.print(timeNow);
        _SERIAL.print(", reqs: "); _SERIAL.println(1);
        //connectionEstablished = false;
        //digitalWrite(ledPin, LOW);
    }
    return req.header.transactionId;
}


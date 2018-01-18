
#include "led_node/Loop.h"
#include "led_node/Components.h"

#ifndef NODE_ALWAYS_ON
int transactionId = 0;
void loop() {
    TIME const timeNow = millis();
    if (RadioMode::listening == mode.state())
    {
        transactionId = ledNodeLoopIf(mode, timeNow);
    }
    else
    {
        //digitalWrite(sendIndicator, HIGH);
        ledNodeLoopElse(radio, mode, transactionId, timeNow);
    }
}
#else
void loop() {

}
#endif

void ledNodeLoop()
{

}
void ledNodeLoopElse(RF24& radio, RadioMode& mode, const int transactionId, TIME const timeNow)
{
    if (mode.swap(timeNow, false))
    {
        _SERIAL.println("tr: "); _SERIAL.println(transactionId);
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
  LedRequest req(0, -1);
  if (radio.available())
  {
    radio.read( &req, sizeof(req) );
    _SERIAL.println(req.get());
  }
  return req;
}
int ledNodeLoopIf(RadioMode& mode, TIME const timeNow)
{
    LedRequest const req = getLedRequest();
    bool reqReceived = false;
    if (req.msgId() == LED_ON_REQUEST)
    {
//      if (!connectionEstablished)
//      {
//          //blinker.begin(timeNow);
//      }
      //blinker.update(timeNow);
//      connectionEstablished = true;
      _SERIAL.println("LED ON");
      digitalWrite(ledPin, HIGH);
      reqReceived = true;
    }
    else if (req.msgId() == LED_OFF_REQUEST)
    {
        _SERIAL.println("LED OFF");
        digitalWrite(ledPin, LOW);
        reqReceived = true;
    }
    if (mode.swap(timeNow, reqReceived))
    {
        //_SERIAL.print(timeNow);
        //_SERIAL.print("trId: "); _SERIAL.println(req.header.transactionId);
        //connectionEstablished = false;
        //digitalWrite(ledPin, LOW);
        radio.flush_rx();
    }
    return req.get();
}


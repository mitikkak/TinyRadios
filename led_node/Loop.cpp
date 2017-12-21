
#include "led_node/Loop.h"
#include "led_node/Components.h"

#ifndef NODE_ALWAYS_ON
void loop() {
    TIME const timeNow = millis();
    if (RadioMode::listening == mode.state())
    {
        ledNodeLoopIf(mode, timeNow, _SERIAL);
    }
    else
    {
        //digitalWrite(sendIndicator, HIGH);
        ledNodeLoopElse(radio, mode, timeNow, _SERIAL);
    }
}
#else
void loop() {

}
#endif

void ledNodeLoop()
{

}
void ledNodeLoopElse(RF24& radio, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL)
{
    if (mode.swap(timeNow, false))
    {
        _SERIAL.println("end of sending period");
        return;
    }
    const Ping req(0,0);
    sendPingResponse(req, radio);
}
Ping getPingRequest()
{
  radio.startListening();
  bool timeout = false;
  Ping req(0,0);
  #if 0
  TIME const started_waiting_at = micros();
  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 10000 ){ // If waited longer than 200ms, indicate timeout and exit while loop
      //_SERIAL.println("timeout");
      timeout = true;
      timeouts++;
      break;
    }
  }
  if (!timeout)
  #else
  if (radio.available())
  #endif
  {
    radio.read( &req, sizeof(req) );
  }
  return req;
}
void ledNodeLoopIf(RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL)
{
    Ping const req = getPingRequest();
    bool reqReceived = false;
    if (req.header.msgId == PING_REQUEST)
    {
//      if (!connectionEstablished)
//      {
//          //blinker.begin(timeNow);
//      }
      //blinker.update(timeNow);
//      connectionEstablished = true;
      digitalWrite(ledPin, HIGH);
      reqReceived = true;
    }
    if (mode.swap(timeNow, reqReceived))
    {
        _SERIAL.print(timeNow);
        _SERIAL.print(", reqs: "); _SERIAL.println(1);
        //connectionEstablished = false;
        //digitalWrite(ledPin, LOW);
        return;
    }
}


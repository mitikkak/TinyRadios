
#include "LedNodeLoop.h"
#include "led_node/Components.h"

void ledNodeLoop()
{

}
void ledNodeLoopElse(Ping const&  req, RF24& radio, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL)
{
    if (mode.swap(timeNow, false))
    {
        _SERIAL.println("end of sending period");
        return;
    }
    sendPingResponse(req, radio);
}
void ledNodeLoopIf(Ping const & req, unsigned int& reqs, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL)
{
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
      reqs++;
      reqReceived = true;
    }
    if (mode.swap(timeNow, reqReceived))
    {
        _SERIAL.print(timeNow);
        _SERIAL.print(", reqs: "); _SERIAL.println(reqs);
        //connectionEstablished = false;
        reqs = 0;
        //digitalWrite(ledPin, LOW);
        return;
    }
}

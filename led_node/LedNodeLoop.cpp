
#include "LedNodeLoop.h"
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
void ledNodeLoopIf(unsigned int& reqs, bool const reqReceived, RadioMode& mode, TIME const timeNow, TinyDebugSerial& _SERIAL)
{
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

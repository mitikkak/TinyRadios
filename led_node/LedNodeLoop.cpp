
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

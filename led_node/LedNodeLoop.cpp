#include "Messages.h"
void ledNodeLoop()
{

}
void ledNodeLoopElse(Ping const&  req, RF24& radio)
{
    sendPingResponse(req, radio);
}

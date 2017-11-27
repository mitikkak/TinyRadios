#include "Messages.h"
#include "RadioMode.h"

RadioMode::RadioMode(TIME const listen, TIME const send)
:state_(inactive),timePrev(0), prevSwapped(0), listenPeriod(listen), sendPeriod(send)
{}
void RadioMode::start(State const initial, TIME const now)
{
    state_ = initial;
    timePrev = now;
    prevSwapped = now;
}
bool RadioMode::swap(TIME const timeNow, bool const msgReceived)
{
    bool retValue = false;
    if (state() == sending)
    {
        if (timeNow - prevSwapped >= sendPeriod)
        {
            prevSwapped = timeNow;
            state_ = listening;
            retValue = true;
        }
    }
    else
    {
        if (msgReceived || timeNow - prevSwapped >= listenPeriod)
        {
            prevSwapped = timeNow;
            state_ = sending;
            retValue = true;
        }

    }
    return retValue;
}
RadioMode::State RadioMode::state() const {return state_;}

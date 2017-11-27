//#include "Components.h"
#include "Messages.h"
#include "RadioMode.h"
//#include "Constants.h"



RadioMode::RadioMode()
:isSending_(false),timePrev(0), prevSwapped(0)
{}
void RadioMode::start(bool const sending, TIME const now)
{
    isSending_ = sending;
    timePrev = now;
    prevSwapped = now;
}
bool RadioMode::swap(TIME const timeNow)
{
    if (timeNow - prevSwapped >= MODE_SWAP_PERIOD)
    {
        prevSwapped = timeNow;
        isSending_ = (isSending_ == true) ? false : true;
        return true;
    }
    return false;
}
bool RadioMode::isSending() const {return isSending_;}

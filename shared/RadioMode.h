
#pragma once
#include "Messages.h"
class RadioMode
{
public:
    enum State
    {
        inactive = 0,
        sending = 1,
        listening = 2
    };

    static constexpr TIME infinite = 0xffffffffffffffff;
    //static TIME constexpr MODE_SWAP_PERIOD = 5000;
    RadioMode(TIME const listen, TIME const send);
    bool swap(TIME const timeNow, bool const msgReceived);
    State state() const;
    void start(State const initial, TIME const now);
private:
    State state_ = inactive;
    TIME timePrev = 0;
    TIME prevSwapped = 0;
    TIME const listenPeriod;
    TIME const sendPeriod;
};

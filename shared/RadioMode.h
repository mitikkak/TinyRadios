
#pragma once
#include "Messages.h"
class RadioMode
{
    bool isSending_ = false;
    TIME timePrev = 0;
    TIME prevSwapped = 0;
public:
    static TIME constexpr MODE_SWAP_PERIOD = 5000;
    RadioMode();
    bool swap(TIME const timeNow);
    bool isSending() const;
    void start(bool const sending, TIME const now);
};

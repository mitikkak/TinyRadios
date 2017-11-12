
#pragma once

class RadioMode
{
    bool isSending_ = false;
    TIME timePrev = 0;
    TIME prevSwapped = 0;
    static TIME constexpr MODE_SWAP_PERIOD = 5000;
public:
    RadioMode();
    bool swap(TIME const timeNow);
    bool isSending() const;
};

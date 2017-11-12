
#pragma once

#include "Messages.h"

void doBlink(const int rounds, const int delay_);

class Blink
{
    const int rounds;
    const TIME delay;
    TIME startTime;
    TIME prevTime;
    TIME endTime;
    int state;
    int pin;
    void swapState();
public:
    Blink(const int rounds_, const TIME delay_, const int pin_);
    void begin(TIME const now);
    void update(TIME const now);
};




#pragma once

#include "Components.h"

void doBlink(const int rounds, const int delay_);

class Blink
{
    const int rounds;
    const TIME delay;
    TIME startTime;
    TIME prevTime;
    TIME endTime;
    int state;
    void swapState();
public:
    Blink(const int rounds_, const TIME delay_);
    void begin(TIME const now);
    void update(TIME const now);
};



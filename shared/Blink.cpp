
#include "Blink.h"
#include "Arduino.h"

void Blink::swapState()
{
    state = (state == HIGH) ? LOW : HIGH;
    digitalWrite(pin, state);
}
Blink::Blink(const int rounds_, const TIME delay_, const int pin_)
: rounds(rounds_), delay(delay_), startTime(0), prevTime(0), endTime(0), state(LOW), pin(pin_)
{
}
void Blink::begin(TIME const now)
{
    startTime = now;
    endTime = now + (rounds * delay);
    digitalWrite(pin, state);
}
void Blink::update(TIME const now)
{
    if (now >= endTime)
    {
        if (state == LOW) {swapState();}
        return;
    }
    else if (now >= (prevTime+delay))
    {
        swapState();
        prevTime = now;
    }
}

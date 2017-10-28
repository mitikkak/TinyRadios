
#include "Blink.h"

void doBlink(const int rounds, const int delay_)
{
  for (int r = 0; r < rounds; r++)
  {
    digitalWrite(ledPin, HIGH);
    delay(delay_);
    digitalWrite(ledPin, LOW);
    delay(delay_);
  }
}
void Blink::swapState()
{
    state = (state == HIGH) ? LOW : HIGH;
    digitalWrite(ledPin, state);
}
Blink::Blink(const int rounds_, const TIME delay_)
: rounds(rounds_), delay(delay_), startTime(0), prevTime(0), endTime(0), state(LOW)
{
}
void Blink::begin(TIME const now)
{
    startTime = now;
    endTime = now + (rounds * delay);
    digitalWrite(ledPin, state);
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

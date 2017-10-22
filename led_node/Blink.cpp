
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

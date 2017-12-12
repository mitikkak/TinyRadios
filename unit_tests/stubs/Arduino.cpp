#include "Arduino.h"
#include <string.h>

unsigned pins[Arduino::numPins] = {LOW};
unsigned Arduino::ledState(unsigned const pin)
{
    assert(pin < numPins);
    return ::pins[pin];
}
void Arduino::reset()
{
    memset(&pins, LOW, sizeof(pins));
}

void digitalWrite(unsigned pin, unsigned state)
{
    assert(pin < Arduino::numPins);
    pins[pin] = state;
}

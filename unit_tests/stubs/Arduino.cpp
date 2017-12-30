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
unsigned long millis()
{
    Arduino::timeNow += Arduino::timeStep;
    return Arduino::timeNow;
}
unsigned long micros()
{
    return millis()*1000;
}
unsigned long Arduino::timeNow = 0;
unsigned long Arduino::timeStep = 1;

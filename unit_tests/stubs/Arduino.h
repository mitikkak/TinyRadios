
#pragma once

typedef char byte;

enum PinState{ LOW, HIGH };

namespace Arduino {

unsigned ledState(unsigned const pin)
{
    return LOW;
}

}



#pragma once
#include "shared/Messages.h"
#include "shared/RadioMode.h"

void sendPingRequest(unsigned int const rounds);
bool onePingRound(RadioMode& mode, unsigned int const receiver, unsigned int const rounds, TIME& timeSpent, unsigned int& attempts);

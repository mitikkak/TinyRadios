
#pragma once
#include "shared/Messages.h"
#include "shared/RadioMode.h"

void sendLedRequest(unsigned int const transactionId, int const msgId);
bool onePingRound(RadioMode& mode, unsigned int const receiver, unsigned int const rounds, TIME& timeSpent, unsigned int& attempts, int const msgId);

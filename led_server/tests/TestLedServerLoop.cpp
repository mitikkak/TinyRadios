#include <gtest/gtest.h>
#include "Arduino.h"
#include "led_server/Loop.h"
#include "led_server/Components.h"
#include "shared/Messages.h"
#include "shared/RadioMode.h"

class TestLedServerLoop : public ::testing::Test {
public:

    void SetUp() {
        Arduino::reset();
    }

    void TearDown() {

    }
};

TEST_F(TestLedServerLoop, PingReq)
{
    unsigned int const rounds = 5;
    sendPingRequest(rounds);
    ASSERT_EQ(radio.stoppedListening(), true);
    const uint8_t* const writeBuffer = radio.written();
    ASSERT_NE(nullptr, writeBuffer);
    Ping req(0, 0);
    const int trId = static_cast<int>(writeBuffer[sizeof(req.header.msgId)]);
    const int msgId = static_cast<int>(writeBuffer[0]);
    ASSERT_EQ(PING_REQUEST, msgId);
    ASSERT_EQ(trId, rounds);
}
#if 1
TEST_F(TestLedServerLoop, onePingRound)
{
    TIME const listenPeriod = 2;
    TIME const sendPeriod = 2;
    unsigned int const receiver = 0;
    RadioMode mode(listenPeriod, sendPeriod);
    unsigned int const rounds = 17;
    TIME timeSpent = 0;
    unsigned int attempts = 0;
    Ping const resp = onePingRound(mode, receiver, rounds, timeSpent, attempts);
    ASSERT_EQ(PING_RESPONSE, resp.header.msgId);
    ASSERT_EQ(rounds, resp.header.transactionId);
    ASSERT_EQ(Arduino::timeNow + sendPeriod, timeSpent);
}
#endif

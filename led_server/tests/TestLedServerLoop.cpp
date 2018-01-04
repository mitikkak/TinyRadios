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
    sendLedRequest(rounds);
    ASSERT_EQ(radio.stoppedListening(), true);
    const uint8_t* const writeBuffer = radio.written();
    ASSERT_NE(nullptr, writeBuffer);
    Ping req(0, 0);
    const int trId = static_cast<int>(writeBuffer[sizeof(req.header.msgId)]);
    const int msgId = static_cast<int>(writeBuffer[0]);
    ASSERT_EQ(LED_REQUEST, msgId);
    ASSERT_EQ(trId, rounds);
}
TEST_F(TestLedServerLoop, onePingRound_respReceivedOnFirstAttempt)
{
    unsigned int const transactionId = 17;
    radio.setMsgId(PING_RESPONSE);
    radio.setTransactionId(transactionId);
    TIME const listenPeriod = 9;
    TIME const sendPeriod = 4;
    unsigned int const receiver = 0;
    RadioMode mode(listenPeriod, sendPeriod);
    TIME timeSpent = 0;
    unsigned int attempts = 0;
    bool const success = onePingRound(mode, receiver, transactionId, timeSpent, attempts);
    ASSERT_EQ(true, success);
    const int causedByAdruinoStub = 1;
    //const int respReceivedOnFirstAttempt = 1;
    //ASSERT_EQ(sendPeriod + respReceivedOnFirstAttempt + causedByAdruinoStub, timeSpent);
    ASSERT_EQ(sendPeriod + listenPeriod + causedByAdruinoStub, timeSpent);
}
TEST_F(TestLedServerLoop, onePingRound_noResp)
{
    unsigned int const transactionId = 17;
    const int msgId = 7777;
    radio.setMsgId(msgId);
    radio.setTransactionId(0);
    TIME const listenPeriod = 6;
    TIME const sendPeriod = 2;
    unsigned int const receiver = 0;
    RadioMode mode(listenPeriod, sendPeriod);
    TIME timeSpent = 0;
    unsigned int attempts = 0;
    bool const success = onePingRound(mode, receiver, transactionId, timeSpent, attempts);
    ASSERT_EQ(false, success);
     const int causedByAdruinoStub = 1;
    ASSERT_EQ(sendPeriod + listenPeriod + causedByAdruinoStub, timeSpent);
}


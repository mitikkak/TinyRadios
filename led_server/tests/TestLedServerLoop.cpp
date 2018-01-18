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
        RF24::readFunctionPtr = 0;
    }
    void sequenceLedReq(const int level)
    {
        unsigned int const expectedTrId = 5;
        sendLedRequest(expectedTrId, level);
        ASSERT_EQ(radio.stoppedListening(), true);
        const uint8_t* const writeBuffer = radio.written();
        ASSERT_NE(nullptr, writeBuffer);
        Ping req(0, 0);
        const int trId = static_cast<int>(writeBuffer[sizeof(req.header.msgId)]);
        const int msgId = static_cast<int>(writeBuffer[0]);
        const int ledLevel = static_cast<int>(writeBuffer[sizeof(req.header)]);
        ASSERT_EQ(msgId, LED_ON_REQUEST);
        ASSERT_EQ(trId, expectedTrId);
        ASSERT_EQ(level, ledLevel);
    }
};

TEST_F(TestLedServerLoop, LedRequestMsg)
{
    const int msgId = 7;
    const int trId = 88;
    const int nodeId = 76;
    LedRequest req(msgId, trId, nodeId);
    ASSERT_EQ(req.msgId(), msgId);
    ASSERT_EQ(req.trId(), trId);
    ASSERT_EQ(req.nodeId(), nodeId);
}

TEST_F(TestLedServerLoop, LedReq_OFF)
{
    sequenceLedReq(Led_OFF);
}
TEST_F(TestLedServerLoop, LedReq_ON)
{
    sequenceLedReq(Led_ON);
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
    bool const success = onePingRound(mode, receiver, transactionId, timeSpent, attempts, Led_OFF);
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
    bool const success = onePingRound(mode, receiver, transactionId, timeSpent, attempts, Led_ON);
    ASSERT_EQ(false, success);
     const int causedByAdruinoStub = 1;
    ASSERT_EQ(sendPeriod + listenPeriod + causedByAdruinoStub, timeSpent);
}


#include <gtest/gtest.h>
#include "LedNodeLoop.h"
#include "RF24.h"

class TestLedNodeLoop : public ::testing::Test {
public:

    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestLedNodeLoop, responsePeriodIsOn)
{
    const int transactionId = 9;
    Ping req(PING_REQUEST,transactionId);
    RF24 radio;
    RadioMode mode(300,300);
    TIME const timeNow = 0;
    TinyDebugSerial serial;
    ledNodeLoopElse(req, radio, mode, timeNow, serial);
    const uint8_t* const writeBuffer = radio.written();
    ASSERT_NE(nullptr, writeBuffer);
    const int respTransactionId = static_cast<int>(writeBuffer[sizeof(req.header.msgId)]);
    const int respMsgId = static_cast<int>(writeBuffer[0]);
    ASSERT_EQ(transactionId, respTransactionId);
    ASSERT_EQ(PING_RESPONSE, respMsgId);
}

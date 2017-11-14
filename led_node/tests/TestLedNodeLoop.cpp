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
    ledNodeLoopElse(req, radio);
    const int respTransactionId = static_cast<int>(radio.written()[sizeof(req.header.msgId)]);
    const int respMsgId = static_cast<int>(radio.written()[0]);
    ASSERT_EQ(transactionId, respTransactionId);
    ASSERT_EQ(PING_RESPONSE, respMsgId);
}

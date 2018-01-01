#include <gtest/gtest.h>
#include "led_node/Loop.h"
#include "RF24.h"
#include "led_node/Components.h"

class TestLedNodeLoop : public ::testing::Test {
public:

    void SetUp() {
        Arduino::reset();
    }

    void TearDown() {

    }
};

TEST_F(TestLedNodeLoop, responsePeriodIsOn)
{
    const int transactionId = 9;
    Ping req(PING_REQUEST,transactionId);
    RadioMode mode(300,300);
    TIME const timeNow = 0;
    TinyDebugSerial serial;
    ledNodeLoopElse(radio, mode, transactionId, timeNow, serial);
    const uint8_t* const writeBuffer = radio.written();
    ASSERT_NE(nullptr, writeBuffer);
    const int respTransactionId = static_cast<int>(writeBuffer[sizeof(req.header.msgId)]);
    const int respMsgId = static_cast<int>(writeBuffer[0]);
    ASSERT_EQ(transactionId, respTransactionId);
    ASSERT_EQ(PING_RESPONSE, respMsgId);
}
TEST_F(TestLedNodeLoop, listeningPeriodIdOn_PingReceived)
{
    const int msgId = PING_REQUEST;
    radio.setMsgId(msgId);
    TIME const timeNow = 6;
    TinyDebugSerial serial;
    ASSERT_EQ("", serial.getPrints());
    ASSERT_EQ(LOW, Arduino::ledState(ledPin));
    RadioMode mode(300,300);
    mode.start(RadioMode::listening, timeNow);
    ASSERT_EQ(RadioMode::listening, mode.state());
    ledNodeLoopIf(mode, timeNow, serial);
    std::string const expectedLog = std::string(std::to_string(timeNow)) + ", reqs: 1";
    ASSERT_EQ(expectedLog, serial.getPrints());
    ASSERT_EQ(HIGH, Arduino::ledState(ledPin));
    ASSERT_EQ(RadioMode::sending, mode.state());
}
TEST_F(TestLedNodeLoop, listeningPeriodIdOn_PingNotReceived)
{
    const int msgId = 7777;
    radio.setMsgId(msgId);
    TIME const timeNow = 6;
    TinyDebugSerial serial;
    RadioMode mode(300,300);
    mode.start(RadioMode::listening, timeNow);
    ledNodeLoopIf(mode, timeNow, serial);
    std::string const expectedLog = "";
    ASSERT_EQ(expectedLog, serial.getPrints());
    ASSERT_EQ(LOW, Arduino::ledState(ledPin));
    ASSERT_EQ(RadioMode::listening, mode.state());
}

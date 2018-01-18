#include <gtest/gtest.h>
#include "led_node/Loop.h"
#include "RF24.h"
#include "led_node/Components.h"

class TestLedNodeLoop : public ::testing::Test {
public:

    static int& msgId()
    {
        static int s_msgId = 0;
        return s_msgId;
    }

    static int& trId()
    {
        static int s_trId = 0;
        return s_trId;
    }

    static int& level()
    {
        static int s_level = Led_OFF;
        return s_level;
    }

    void SetUp() {
        Arduino::reset();
    }

    void TearDown() {
        RF24::readFunctionPtr = 0;
    }

    static void ledRequestReader(void* handle, unsigned const size)
    {
        LedRequest* req = static_cast<LedRequest*>(handle);
        req->setMsgId(msgId());
        req->setTrId(trId());
    }

    void setLedRequestReader(int msgId_, int trId_, int level_)
    {
        msgId() = msgId_;
        trId() = trId_;
        level() = level_;
        RF24::readFunctionPtr = &ledRequestReader;
    }
    void sequenceLedReqReceived(int const ledLevel, const int ledState)
    {
        Arduino::reset();
        const int msgId = LED_ON_REQUEST;
        radio.setMsgId(msgId);
        TIME const timeNow = 6;
        TinyDebugSerial serial;
        const int expectedTransactionId = 98;
        setLedRequestReader(msgId, expectedTransactionId, ledLevel);
        ASSERT_EQ("", serial.getPrints());
        ASSERT_EQ(LOW, Arduino::ledState(ledPin));
        RadioMode mode(300,300);
        mode.start(RadioMode::listening, timeNow);
        ASSERT_EQ(RadioMode::listening, mode.state());
        const int transactionId = ledNodeLoopIf(mode, timeNow);
        std::string const expectedLog = std::string(std::to_string(timeNow)) + ", reqs: 1";
        ASSERT_EQ(expectedTransactionId, transactionId);
        ASSERT_EQ(expectedLog, serial.getPrints());
        ASSERT_EQ(ledState, Arduino::ledState(ledPin));
        ASSERT_EQ(RadioMode::sending, mode.state());
    }
};

TEST_F(TestLedNodeLoop, responsePeriodIsOn)
{
    const int transactionId = 9;
    Ping req(PING_REQUEST,transactionId);
    RadioMode mode(300,300);
    TIME const timeNow = 0;
    TinyDebugSerial serial;
    ledNodeLoopElse(radio, mode, transactionId, timeNow);
    const uint8_t* const writeBuffer = radio.written();
    ASSERT_NE(nullptr, writeBuffer);
    const int respTransactionId = static_cast<int>(writeBuffer[sizeof(req.header.msgId)]);
    const int respMsgId = static_cast<int>(writeBuffer[0]);
    ASSERT_EQ(transactionId, respTransactionId);
    ASSERT_EQ(PING_RESPONSE, respMsgId);
}
TEST_F(TestLedNodeLoop, listeningPeriodIdOn_LedReqReceived)
{
    sequenceLedReqReceived(Led_OFF, LOW);
    sequenceLedReqReceived(Led_ON, HIGH);
}
TEST_F(TestLedNodeLoop, listeningPeriodIdOn_PingNotReceived)
{
    const int msgId = 7777;
    radio.setMsgId(msgId);
    TIME const timeNow = 6;
    TinyDebugSerial serial;
    RadioMode mode(300,300);
    mode.start(RadioMode::listening, timeNow);
    ledNodeLoopIf(mode, timeNow);
    std::string const expectedLog = "";
    ASSERT_EQ(expectedLog, serial.getPrints());
    ASSERT_EQ(LOW, Arduino::ledState(ledPin));
    ASSERT_EQ(RadioMode::listening, mode.state());
}

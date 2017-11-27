
#include <gtest/gtest.h>
#include "RadioMode.h"

class TestRadioMode : public ::testing::Test {
public:

    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestRadioMode, passiveRole)
{
    TIME const beginning = 5;
    TIME const listenPeriod = RadioMode::infinite;
    TIME const sendPeriod = 5000;
    RadioMode mode(listenPeriod, sendPeriod);
    mode.start(RadioMode::listening, beginning);
    ASSERT_EQ(RadioMode::listening, mode.state());
    TIME const requestReceived = beginning;
    mode.swap(requestReceived, true);
    ASSERT_EQ(RadioMode::sending, mode.state());
    mode.swap(requestReceived + sendPeriod-1, false);
    ASSERT_EQ(RadioMode::sending, mode.state());
    mode.swap(requestReceived + sendPeriod, false);
    ASSERT_EQ(RadioMode::listening, mode.state());
}
TEST_F(TestRadioMode, activeRoleNoResp)
{
    TIME const beginning = 5;
    TIME const listenPeriod = 5000;
    TIME const sendPeriod = 500;
    RadioMode mode(listenPeriod, sendPeriod);
    mode.start(RadioMode::sending, beginning);
    ASSERT_EQ(RadioMode::sending, mode.state());
    ASSERT_EQ(false, mode.swap(beginning + sendPeriod-1, false));
    ASSERT_EQ(RadioMode::sending, mode.state());
    ASSERT_EQ(true, mode.swap(beginning + sendPeriod, false));
    ASSERT_EQ(RadioMode::listening, mode.state());
    ASSERT_EQ(false, mode.swap(beginning + sendPeriod + listenPeriod -1, false ));
    ASSERT_EQ(RadioMode::listening, mode.state());
    ASSERT_EQ(true, mode.swap(beginning + sendPeriod + listenPeriod, false ));
    ASSERT_EQ(RadioMode::sending, mode.state());
}
TEST_F(TestRadioMode, activeRoleRespReceived)
{
    TIME const beginning = 5;
    TIME const listenPeriod = 5000;
    TIME const sendPeriod = 500;
    RadioMode mode(listenPeriod, sendPeriod);
    mode.start(RadioMode::sending, beginning);
    ASSERT_EQ(RadioMode::sending, mode.state());
    ASSERT_EQ(false, mode.swap(beginning + sendPeriod-1, false));
    ASSERT_EQ(RadioMode::sending, mode.state());
    ASSERT_EQ(true, mode.swap(beginning + sendPeriod, false));
    ASSERT_EQ(RadioMode::listening, mode.state());
    ASSERT_EQ(true, mode.swap(beginning + sendPeriod + listenPeriod -1, true ));
    ASSERT_EQ(RadioMode::sending, mode.state());
}


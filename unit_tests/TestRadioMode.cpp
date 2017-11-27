
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
    RadioMode mode;
    TIME const beginning = 5;
    mode.start(false, beginning);
    ASSERT_EQ(false, mode.isSending());
    TIME const requestReceived = beginning;
    mode.swap(requestReceived);
    ASSERT_EQ(true, mode.isSending());
    mode.swap(requestReceived + RadioMode::MODE_SWAP_PERIOD-1);
    ASSERT_EQ(true, mode.isSending());
    mode.swap(requestReceived + RadioMode::MODE_SWAP_PERIOD);
    ASSERT_EQ(false, mode.isSending());
}


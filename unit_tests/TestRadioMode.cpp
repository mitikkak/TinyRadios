
#include <gtest/gtest.h>

class TestRadioMode : public ::testing::Test {
public:

    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestRadioMode, nothing)
{
    ASSERT_EQ(1,1);
}


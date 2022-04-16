#include "ComputeAngle.cpp"
#include <gtest/gtest.h>

TEST(ComputeAngleTest, angle_output_test)
{
    ComputeAngle CompA;

    CompA.setRSSI(-20,-36,-72);

    float ang = CompA.getAngle();
    float a = CompA.get_a();

    ASSERT_EQ(0, ang);
    ASSERT_EQ(0, a);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


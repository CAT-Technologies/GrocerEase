#include "../../src/ComputeAngle.cpp"
#include <gtest/gtest.h>

TEST(ComputeAngleTest, angle_output_test)
{
    ComputeAngle CompA;

    pair<float,float> details = CompA.computeAngleRSSI(-55,-55,-50);

    float ang = CompA.roundoff(details.first,2);
    
    ASSERT_EQ(ang,0.7f);
    
}

TEST(ComputeAngleTest, a_output_test_1)
{
    ComputeAngle CompA;

    pair<float,float> details = CompA.computeAngleRSSI(-55,-55,-50);

    float a = CompA.roundoff(details.second,2);

    ASSERT_EQ(a, 1.26f);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


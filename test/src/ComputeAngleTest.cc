#include "../../src/ComputeAngle.cpp"
#include <gtest/gtest.h>

TEST(ComputeAngleTest, angle_output_test)
{
    ComputeAngle CompA;

    pair<float,float> details = CompA.computeAngleRSSI(-55,-55,-50);

    float ang = details.first;
    float a = details.second;

    ASSERT_EQ(0.0f, ang);
    ASSERT_EQ(0.0f, a);
}

// TEST(ComputeAngleTest, a_output_test_1)
// {
//     ComputeAngle CompA;
// 
//     CompA.setRSSI(-352,-352,-377);
// 
//     float ang = CompA.getAngle();
//     float a = CompA.get_a();
// 
//     std::cout<< a;
//     ASSERT_EQ(0, a);
// }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


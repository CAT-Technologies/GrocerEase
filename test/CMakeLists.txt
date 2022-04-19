cmake_minimum_required(VERSION 2.6)
project(ComputeAngleTest)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(test src/ComputeAngleTest.cc)
target_link_libraries(test ${GTEST_LIBRARIES} pthread)
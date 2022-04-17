cmake_minimum_required(VERSION 3.10.2)
project(computeAngle)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(computeAngle
  src/cart.cpp
  src/test_cart.cpp
  include/cart.h
)

target_link_libraries(computeAngle pigpio rt)

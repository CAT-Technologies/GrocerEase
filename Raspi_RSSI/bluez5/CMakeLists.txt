cmake_minimum_required(VERSION 3.10.2)
project(bluez5)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(bluez5
  src/RSSI_bluez.cpp
)

target_link_libraries(bluez5 bluetooth)


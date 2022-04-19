cmake_minimum_required(VERSION 3.10.2)
project(rssi_basic_scan)

set(CMAKE_CXX_STANDARD 11)

add_executable(rssi_basic_scan
  src/rssi.cpp
)

target_link_libraries(rssi_basic_scan bluetooth)

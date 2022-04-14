cmake_minimum_required(VERSION 3.10.2)
project(rssi_M)

set(CMAKE_CXX_STANDARD 11)

add_executable(rssi_M
  src/rssi.cpp
)

target_link_libraries(rssi_M bluetooth)

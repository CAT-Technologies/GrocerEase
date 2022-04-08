cmake_minimum_required(VERSION 3.10.2)
project(rssi_mit)

set(CMAKE_CXX_STANDARD 11)

add_executable(rssi_mit
  src/rssi.cpp
)

target_link_libraries(rssi_mit bluetooth)

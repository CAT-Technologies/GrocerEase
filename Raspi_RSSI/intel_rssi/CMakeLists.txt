cmake_minimum_required(VERSION 3.10.2)
project(intel_rssi)

set(CMAKE_CXX_STANDARD 11)

add_executable(intel_rssi
  src/simple.c
)

target_link_libraries(intel_rssi bluetooth)

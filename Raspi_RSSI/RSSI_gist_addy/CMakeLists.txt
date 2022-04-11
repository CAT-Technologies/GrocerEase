cmake_minimum_required(VERSION 3.10.2)
project(RSSI)

set(CMAKE_CXX_STANDARD 11)

add_executable(RSSI_gist_addy
  src/rssi.cpp
)

target_link_libraries(RSSI bluetooth)


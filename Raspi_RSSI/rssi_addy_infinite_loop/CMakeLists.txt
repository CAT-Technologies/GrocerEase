cmake_minimum_required(VERSION 3.10.2)
project(rssi)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(rssi 
  src/rssi.c
)

target_link_libraries(rssi bluetooth)



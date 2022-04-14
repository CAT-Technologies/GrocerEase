cmake_minimum_required(VERSION 3.10.2)
project(bitbucket_david_init1)

set(CMAKE_CXX_STANDARD 11)
add_executable(bitbucket_david_init1 
  src/get_RSSI_bitbucket.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)

if (GLIB_PKG_FOUND)
    message(Found glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
ENDIF()

#find_package(bluetooth REQUIRED)

target_link_libraries(bitbucket_david_init1 bluetooth)

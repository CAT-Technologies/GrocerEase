cmake_minimum_required(VERSION 3.10.2)
project(rssi_1)

set(CMAKE_CXX_STANDARD 11)
add_executable(rssi_1 
  src/rssi_1.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)
pkg_check_modules(GLIB glib-2.0 gio-2.0 REQUIRED)

if (GLIB_PKG_FOUND)
    message(Found glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
ENDIF()

target_link_libraries(rssi_1 bluetooth)
target_link_libraries(rssi_1 ${GLIB_LIBRARIES})

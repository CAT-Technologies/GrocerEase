cmake_minimum_required(VERSION 3.10.2)
project(rssi_detailing)

set(CMAKE_CXX_STANDARD 11)
add_executable(rssi_detailing 
  src/rssi_details.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)
pkg_check_modules(GLIB glib-2.0 gio-2.0 REQUIRED)

if (GLIB_PKG_FOUND)
    message(Found glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
ENDIF()

target_link_libraries(rssi_detailing bluetooth)
target_link_libraries(rssi_detailing ${GLIB_LIBRARIES})

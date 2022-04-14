cmake_minimum_required(VERSION 3.10.2)
project(bl_dbus)

set(CMAKE_CXX_STANDARD 11)
add_executable(bl_dbus 
  src/bluez_dbus.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)

if (GLIB_PKG_FOUND)
    message(Found glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
ENDIF()

target_link_libraries(bl_dbus bluetooth)

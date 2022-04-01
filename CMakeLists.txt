# toplevel CMakeLists.txt for a catkin workspace
# catkin/cmake/toplevel.cmake

cmake_minimum_required(VERSION 3.10.2)

set(PROJECT "GrocerEase")
project("${PROJECT}_Project" VERSION 1.2.3 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

# Options
option(ENABLE_WARNINGS      "Enable to add warnings to a target."   ON)
option(ENABLE_TESTING       "Enable a Unit Testing build."          ON)
option(ENABLE_COVERAGE      "Enable a Code Coverage build."         ON)

# Cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)
include(Warnings)
if (ENABLE_TESTING OR ENABLE_COVERAGE)
    include(CTest)
endif()

add_subdirectory(external)

add_subdirectory(src)

include_directories(include)

add_executable(GrocerEase
  src/GPIO.cc
  include/GPIO.hh)

# Include WiringPi directories
#find_package(WiringPi REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS})

# Link against libraries
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(GrocerEase ${WIRINGPI_LIBRARIES})

install(TARGETS ${EXECUTABLE_NAME}
        EXPORT ${LIBRARY_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(TARGETS ${LIBRARY_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

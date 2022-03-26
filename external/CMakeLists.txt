# WiringPi
set(LIBRARY_INCLUDES "/WiringPi")
add_library(WiringPi INTERFACE)
target_include_directories(WiringPi SYSTEM INTERFACE ${LIBRARY_INCLUDES})

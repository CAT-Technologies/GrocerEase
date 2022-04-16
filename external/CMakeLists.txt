# WiringPi
set(LIBRARY_INCLUDES "/WiringPi")
add_library(WiringPi INTERFACE)
target_include_directories(WiringPi SYSTEM INTERFACE ${LIBRARY_INCLUDES})

set(LIBRARY_INCLUDES "/pigpio")
add_library(pigpio INTERFACE)
target_include_directories(pigpio SYSTEM INTERFACE ${LIBRARY_INCLUDES})

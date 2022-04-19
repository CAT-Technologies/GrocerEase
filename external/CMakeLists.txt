# WiringPi
set(LIBRARY_INCLUDES "/WiringPi")
add_library(WiringPi INTERFACE)
target_include_directories(WiringPi SYSTEM INTERFACE ${LIBRARY_INCLUDES})

# pgpio
set(LIBRARY_INCLUDES "/pgpio")
add_library(pgpio INTERFACE)
target_include_directories(pgpio SYSTEM INTERFACE ${LIBRARY_INCLUDES})

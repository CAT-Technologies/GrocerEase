# Sources
set(LIBRARY_SOURCES "ComputeAngle.cpp")
set(LIBRARY_SOURCES "GPIO.cpp")
set(LIBRARY_SOURCES "cart.cpp")
set(LIBRARY_HEADERS "${PROJECT_SOURCE_DIR}/include/GPIO.h")
set(LIBRARY_INCLUDES "${PROJECT_SOURCE_DIR}/include/cart.h")

# add libraries, targets, and compile them
target_set_warnings(TARGET ${LIBRARY_NAME} ENABLE OFF AS_ERROR OFF)

if(${ENABLE_LTO})
target_enable_lto(${LIBRARY_NAME} optimized)
endif()


# Sources
set(LIBRARY_SOURCES "ComputeAngle.cc")
set(LIBRARY_SOURCES "GPIO.cc")
set(LIBRARY_HEADERS "${PROJECT_SOURCE_DIR}/include/GPIO.hh")
set(LIBRARY_INCLUDES "${PROJECT_SOURCE_DIR}/include/")

# add libraries, targets, and compile them
target_set_warnings(TARGET ${LIBRARY_NAME} ENABLE OFF AS_ERROR OFF)

if(${ENABLE_LTO})
target_enable_lto(${LIBRARY_NAME} optimized)
endif()


# Sources
set(LIBRARY_SOURCES "compute_angle.cc")
set(LIBRARY_SOURCES "GPIO.cc")
set(LIBRARY_SOURCES "main_program.cc")
set(LIBRARY_SOURCES "write_program.cc")

# add libraries, targets, and compile them
#add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES}${LIBRARY_HEADERS})
#target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})
#target_link_libraries(${LIBRARY_NAME} PUBLIC linalg)
#target_link_libraries(${LIBRARY_NAME} PUBLIC loguru)
#target_link_libraries(${LIBRARY_NAME} PUBLIC ${CONAN_CXXOPTS})
#target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
#target_set_warnings(TARGET ${LIBRARY_NAME} ENABLE OFF AS_ERROR OFF))
if(${ENABLE_LTO})
target_enable_lto(${LIBRARY_NAME} optimized)
endif()


cmake_minimum_required(VERSION 3.27)

project(ray-tracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)


add_executable(Main main.cpp)

# # add_subdirectory follows the CMakeLists.txt in the specified directory 
add_subdirectory(src/)
# add_subdirectory(tests/)
# add_subdirectory(third_party/googletest/)

# # src is the name of library (aka. consistent with src in target_include_directories(src PUBLIC <include directories>))
target_link_libraries(Main PUBLIC src)

# enable_testing ()
# # NAME: name of the test 
# # COMMAND: existing executable 
# add_test (NAME ScfTest COMMAND ScfTest)

# Add a custom command to run the command after building
# Specify the output directory for the executable Main 
# `CMAKE_SOURCE_DIR`  this is the directory which contains the top-level `CMakeLists.txt`, i.e. the top level source directory.
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/)

# # Add custom command to run the executable after build
add_custom_command(TARGET Main POST_BUILD
    COMMAND ${CMAKE_SOURCE_DIR}/Main > ${CMAKE_SOURCE_DIR}/img.ppm
    COMMENT "Running Main and generating img.ppm"
)
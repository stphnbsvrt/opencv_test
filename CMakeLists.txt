####################################################
# Cmake settings
####################################################
cmake_minimum_required (VERSION 3.9.1)

#output all the toys here
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

####################################################
# Compiler options
####################################################

#TODO: something other than gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Werror -Wpedantic -Wextra)
else()
    message(FATAL_ERROR "Compiler not supported")
endif()

####################################################
# Directory locations
####################################################
set(STREAMER_DIR ${CMAKE_SOURCE_DIR}/common/streamer)

####################################################
# Include them
####################################################
include_directories(${STREAMER_DIR})

####################################################
# Common source files
####################################################
set(STREAMER_SRC_FILES ${STREAMER_DIR}/streamer.cpp)

####################################################
# Defined
####################################################
add_definitions(-D_SOURCE_DIR_="${CMAKE_SOURCE_DIR}")

####################################################
# Project directories
####################################################
add_subdirectory(hello_camera)
add_subdirectory(tests)

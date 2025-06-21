# Project 1: Vector
project(llm_vector VERSION 0.1.0)

# This is a header-only library
add_library(llm_vector INTERFACE)
target_include_directories(llm_vector INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add subdirectories
add_subdirectory(examples)
add_subdirectory(tests)

# Project 1: Vector
project(token_processing VERSION 0.1.0)

add_library(
    token_processing src/bpe.cpp
)
# PUBLIC means:
# 1. This directory is used when compiling token_processing itself.
# 2. Any other target that links to token_processing will also get this include directory.
target_include_directories(token_processing
    PUBLIC
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        $<INSTALL_INTERFACE:include>
)

# Add subdirectories
add_subdirectory(examples)
#add_subdirectory(tests)

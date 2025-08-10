# Project 3: Multithreading token processing
project(multi_threading_token_processing VERSION 0.1.0)

add_library(
    multi_threading_token_processing src/llminferenceengine.cpp
)

target_include_directories(multi_threading_token_processing
    PUBLIC
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        $<INSTALL_INTERFACE:include>
)

# Add subdirectories
add_subdirectory(examples)
#add_subdirectory(tests)

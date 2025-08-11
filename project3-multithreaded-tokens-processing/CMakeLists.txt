# Project 3: Multithreading token processing
project(multi_threading_token_processing VERSION 0.1.0)

# Need to add this manually
find_package(Threads REQUIRED)

add_library(
    multi_threading_token_processing src/llminferenceengine.cpp
)

target_include_directories(multi_threading_token_processing
    PUBLIC
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(multi_threading_token_processing
    PUBLIC
        Threads::Threads
)

# Add subdirectories
add_subdirectory(examples)
#add_subdirectory(tests)

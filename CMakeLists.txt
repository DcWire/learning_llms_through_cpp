cmake_minimum_required(VERSION 3.10)
project(learning_llms_through_cpp VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add projects
add_subdirectory(project1-llmvector)

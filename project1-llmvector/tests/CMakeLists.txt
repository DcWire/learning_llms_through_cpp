# Test executable
add_executable(vector_tests llmvector_tests.cpp)
target_link_libraries(vector_tests PRIVATE llm_vector)

# Add the test
add_test(NAME vector_tests COMMAND vector_tests)

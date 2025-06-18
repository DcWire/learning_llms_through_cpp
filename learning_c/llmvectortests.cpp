
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "llmvector.h"

// Test result tracking
struct TestResults {
    int passed = 0;
    int total = 0;
    
    void addTest(bool result, const std::string& testName) {
        total++;
        if (result) {
            passed++;
            std::cout << "✓ PASS: " << testName << std::endl;
        } else {
            std::cout << "✗ FAIL: " << testName << std::endl;
        }
    }
    
    void printSummary() const {
        std::cout << "\n=== TEST SUMMARY ===" << std::endl;
        std::cout << "Tests passed: " << passed << "/" << total << std::endl;
        if (passed == total) {
            std::cout << "🎉 ALL TESTS PASSED! 🎉" << std::endl;
        } else {
            std::cout << "❌ Some tests failed." << std::endl;
        }
    }
};

TestResults results;

bool testInitialization() {
    std::cout << "\n=== Testing Initialization ===" << std::endl;
    
    // Test default constructor
    LLMVector<int> defaultVec;
    results.addTest(defaultVec.getSize() == 0, "Default constructor creates empty vector");
    results.addTest(defaultVec.getCapacity() >= 10, "Default constructor has minimum capacity");
    results.addTest(defaultVec.empty(), "Default vector is empty");
    
    // Test parameterized constructor
    const size_t TEST_CAPACITY = 50;
    LLMVector<int> paramVec(TEST_CAPACITY);
    results.addTest(paramVec.getSize() == 0, "Parameterized constructor creates empty vector");
    results.addTest(paramVec.getCapacity() >= TEST_CAPACITY, "Parameterized constructor respects capacity");
    
    // Test with different types
    LLMVector<float> floatVec;
    LLMVector<std::string> stringVec;
    results.addTest(floatVec.getSize() == 0, "Float vector construction works");
    results.addTest(stringVec.getSize() == 0, "String vector construction works");
    
    return true;
}

bool testPushBackAndAccess() {
    std::cout << "\n=== Testing Push Back and Access ===" << std::endl;
    
    const size_t TEST_SIZE = 20;
    LLMVector<int> vi;
    std::vector<int> reference;
    
    // Set seed for reproducible tests
    srand(42);
    
    // Test push_back with random values
    for (size_t i = 0; i < TEST_SIZE; i++) {
        int temp = rand() % 100;
        reference.push_back(temp);
        vi.push_back(temp);
    }
    
    results.addTest(vi.getSize() == TEST_SIZE, "Size correct after push_back operations");
    
    // Test element access
    bool elementsMatch = true;
    for (size_t i = 0; i < TEST_SIZE; i++) {
        if (reference[i] != vi.at(i)) {
            elementsMatch = false;
            break;
        }
    }
    results.addTest(elementsMatch, "All elements match reference vector");
    
    // Test capacity growth
    size_t initialCapacity = vi.getCapacity();
    for (int i = 0; i < 100; ++i) {
        vi.push_back(i);
    }
    results.addTest(vi.getCapacity() > initialCapacity, "Capacity grows when needed");
    results.addTest(vi.getSize() == TEST_SIZE + 100, "Size correct after capacity growth");
    
    return true;
}

bool testBoundsChecking() {
    std::cout << "\n=== Testing Bounds Checking ===" << std::endl;
    
    LLMVector<int> vec;
    
    // Test access on empty vector
    bool caughtEmptyException = false;
    try {
        vec.at(0);
    } catch (const std::out_of_range&) {
        caughtEmptyException = true;
    }
    results.addTest(caughtEmptyException, "Accessing empty vector throws exception");
    
    // Add one element
    vec.push_back(42);
    
    // Test valid access
    bool validAccessWorks = false;
    try {
        int val = vec.at(0);
        validAccessWorks = (val == 42);
    } catch (...) {
        validAccessWorks = false;
    }
    results.addTest(validAccessWorks, "Valid access works correctly");
    
    // Test access beyond size
    bool caughtOutOfRangeException = false;
    try {
        vec.at(1);
    } catch (const std::out_of_range&) {
        caughtOutOfRangeException = true;
    }
    results.addTest(caughtOutOfRangeException, "Accessing beyond size throws exception");
    
    return true;
}

bool testCopySemantics() {
    std::cout << "\n=== Testing Copy Semantics ===" << std::endl;
    
    // Create source vector
    LLMVector<int> source;
    for (int i = 0; i < 15; ++i) {
        source.push_back(i * 10);
    }
    
    // Test copy constructor
    LLMVector<int> copyConstructed(source);
    results.addTest(copyConstructed.getSize() == source.getSize(), "Copy constructor preserves size");
    
    // Verify deep copy
    bool elementsMatch = true;
    for (size_t i = 0; i < copyConstructed.getSize(); ++i) {
        if (copyConstructed.at(i) != source.at(i)) {
            elementsMatch = false;
            break;
        }
    }
    results.addTest(elementsMatch, "Copy constructor creates correct deep copy");
    
    // Test independence
    copyConstructed.push_back(999);
    results.addTest(copyConstructed.getSize() != source.getSize(), "Copied vector is independent");
    
    // Test copy assignment
    LLMVector<int> copyAssigned;
    copyAssigned.push_back(123); // Give it some initial data
    copyAssigned = source;
    
    results.addTest(copyAssigned.getSize() == source.getSize(), "Copy assignment preserves size");
    
    elementsMatch = true;
    for (size_t i = 0; i < copyAssigned.getSize(); ++i) {
        if (copyAssigned.at(i) != source.at(i)) {
            elementsMatch = false;
            break;
        }
    }
    results.addTest(elementsMatch, "Copy assignment creates correct deep copy");
    
    // Test self-assignment
    LLMVector<int> selfTest;
    for (int i = 0; i < 5; ++i) {
        selfTest.push_back(i);
    }
    size_t originalSize = selfTest.getSize();
    
    selfTest = selfTest; // Self-assignment
    results.addTest(selfTest.getSize() == originalSize, "Self-assignment preserves size");
    results.addTest(selfTest.at(0) == 0 && selfTest.at(4) == 4, "Self-assignment preserves data");
    
    return true;
}

bool testMoveSemantics() {
    std::cout << "\n=== Testing Move Semantics ===" << std::endl;
    
    // Test move constructor
    LLMVector<int> source;
    for (int i = 0; i < 10; ++i) {
        source.push_back(i * 5);
    }
    size_t originalSize = source.getSize();
    
    LLMVector<int> moved(std::move(source));
    results.addTest(moved.getSize() == originalSize, "Move constructor transfers size");
    results.addTest(source.getSize() == 0, "Moved-from vector is empty");
    results.addTest(moved.at(0) == 0 && moved.at(9) == 45, "Move constructor transfers data correctly");
    
    // Test move assignment
    LLMVector<int> source2;
    for (int i = 0; i < 8; ++i) {
        source2.push_back(i * 3);
    }
    
    LLMVector<int> target;
    target.push_back(999); // Give target some initial data
    
    size_t originalSize2 = source2.getSize();
    target = std::move(source2);
    
    results.addTest(target.getSize() == originalSize2, "Move assignment transfers size");
    results.addTest(source2.getSize() == 0, "Moved-from vector is empty after assignment");
    results.addTest(target.at(0) == 0 && target.at(7) == 21, "Move assignment transfers data correctly");
    
    return true;
}

bool testCapacityManagement() {
    std::cout << "\n=== Testing Capacity Management ===" << std::endl;
    
    LLMVector<int> vec;
    size_t initialCapacity = vec.getCapacity();
    
    // Test reserve with smaller capacity
    vec.reserve(5);
    results.addTest(vec.getCapacity() >= initialCapacity, "Reserve doesn't shrink capacity");
    
    // Test reserve with larger capacity
    vec.reserve(1000);
    results.addTest(vec.getCapacity() >= 1000, "Reserve increases capacity");
    results.addTest(vec.getSize() == 0, "Reserve doesn't affect size");
    
    // Test efficient push_back after reserve
    size_t capacityBeforePush = vec.getCapacity();
    for (int i = 0; i < 500; ++i) {
        vec.push_back(i);
    }
    results.addTest(vec.getCapacity() == capacityBeforePush, "No reallocation after sufficient reserve");
    
    return true;
}

bool testLLMUseCases() {
    std::cout << "\n=== Testing LLM-Specific Use Cases ===" << std::endl;
    
    // Test token sequence storage
    LLMVector<int> tokenSequence;
    tokenSequence.reserve(512); // Common max sequence length
    
    // Simulate tokenizing "Hello world, this is a test sentence"
    int tokens[] = {15496, 995, 11, 428, 318, 257, 1332, 6827};
    for (int token : tokens) {
        tokenSequence.push_back(token);
    }
    
    results.addTest(tokenSequence.getSize() == 8, "Token sequence has correct length");
    results.addTest(tokenSequence.at(0) == 15496, "First token is correct");
    
    // Test embedding storage
    LLMVector<float> embeddings;
    embeddings.reserve(768); // Common embedding dimension
    
    for (int i = 0; i < 100; ++i) {
        embeddings.push_back(static_cast<float>(i) * 0.01f);
    }
    
    results.addTest(embeddings.getSize() == 100, "Embedding vector has correct size");
    results.addTest(std::abs(embeddings.at(50) - 0.5f) < 0.001f, "Embedding values are correct");
    
    // Test batch processing simulation
    LLMVector<LLMVector<int>> batchSequences;
    
    for (int seq = 0; seq < 5; ++seq) {
        LLMVector<int> sequence;
        for (int token = 0; token < (seq + 1) * 10; ++token) {
            sequence.push_back(token);
        }
        batchSequences.push_back(std::move(sequence));
    }
    
    results.addTest(batchSequences.getSize() == 5, "Batch contains correct number of sequences");
    results.addTest(batchSequences.at(2).getSize() == 30, "Variable length sequences work");
    
    return true;
}

bool testMemoryManagement() {
    std::cout << "\n=== Testing Memory Management ===" << std::endl;
    
    // Test multiple allocations and deallocations
    for (int iteration = 0; iteration < 100; ++iteration) {
        LLMVector<std::string> vec;
        for (int i = 0; i < 50; ++i) {
            vec.push_back("String " + std::to_string(i));
        }
        // Vector goes out of scope - destructor should clean up
    }
    results.addTest(true, "Multiple allocation/deallocation cycles complete");
    
    // Test with zero capacity
    LLMVector<int> vec(0);
    vec.push_back(1);
    results.addTest(vec.getSize() == 1, "Zero capacity vector can still grow");
    results.addTest(vec.at(0) == 1, "Zero capacity vector stores elements correctly");
    
    // Test clear functionality
    LLMVector<int> clearTest;
    for (int i = 0; i < 10; ++i) {
        clearTest.push_back(i);
    }
    size_t capacityBeforeClear = clearTest.getCapacity();
    clearTest.clear();
    
    results.addTest(clearTest.getSize() == 0, "Clear makes vector empty");
    results.addTest(clearTest.empty(), "Vector reports empty after clear");
    results.addTest(clearTest.getCapacity() == capacityBeforeClear, "Clear preserves capacity");
    
    return true;
}

void runTests() {
    std::cout << "LLMVector Comprehensive Test Suite" << std::endl;
    std::cout << "==================================" << std::endl;
    
    try {
        testInitialization();
        testPushBackAndAccess();
        testBoundsChecking();
        testCopySemantics();
        testMoveSemantics();
        testCapacityManagement();
        testLLMUseCases();
        testMemoryManagement();
        
        results.printSummary();
        
    } catch (const std::exception& e) {
        std::cout << "\nTest suite crashed with exception: " << e.what() << std::endl;
    }
}

//
//  llmvectortests.cpp
//  learning_c
//
//  Created by Mohammed Anas Ali on 15/06/25.
//


#include <iostream>
#include <vector>
#include "llmvectortests.h"
#include "llmvector.h"


bool testInitialization() {
    const size_t TEST_SIZE=20;
    LLMVector<int> vi(TEST_SIZE);
    std::vector<int> test(TEST_SIZE);
    
    for(size_t i=0; i<TEST_SIZE; i++) {
        int temp = rand() % 40;
        test[i] = temp;
        vi.push_back(temp);
    }
    
    
    if (vi.getSize() != TEST_SIZE) {
        std::cout<<"Incorrect size of vector\n";
        return false;
    }
    
    for(size_t i=0; i<TEST_SIZE; i++) {
        if(test[i] != vi.at(i)) {
            std::cout<<"Wrong values inserted\n";
            return false;
        }
    }
    
    return true;
}
bool testCopy() {
    const size_t TEST_SIZE=20;
    LLMVector<int> vi(TEST_SIZE);
    
    for(size_t i=0; i<TEST_SIZE; i++) {
        int temp = rand() % 40;
        vi.push_back(temp);
    }
    
    LLMVector<int> other(vi);
    
    for(size_t i=0; i<TEST_SIZE; i++) {
        if(other.at(i) != vi.at(i)) return false;
    }
    return true;
}
bool testAssignmentOperator() {
    const size_t TEST_SIZE=20;
    LLMVector<int> vi(TEST_SIZE);
    
    for(size_t i=0; i<TEST_SIZE; i++) {
        int temp = rand() % 40;
        vi.push_back(temp);
    }
    
    LLMVector<int> other = vi;
    
    for(size_t i=0; i<TEST_SIZE; i++) {
        if(other.at(i) != vi.at(i)) return false;
    }
    return true;
    
}
bool testCapcityLimit();


void runTests() {
    int count = 0;
    count += testInitialization();
    count += testCopy();
    count += testAssignmentOperator();
    
    std::cout << "Number of tests passed: "<<count<<" out of 3\n";
    
}


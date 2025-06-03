//
//  vector.cpp
//  learning_c
//
//  Created by Mohammed Anas Ali on 14/06/25.
//

/* Assignment 1: Memory Management Fundamentals
Objective: Understand manual memory management critical for efficient LLM implementations
TODO: Complete the implementation of this custom vector class optimized for LLM token storage */

#include<iostream>
#include "llmvector.h"

template <typename T>
class LLMVector {
public:
    // A constructor to intialize the data pointer
    LLMVector(size_t initalCapacity = 10):
        data{new T[initalCapacity]},
        capacity{initalCapacity},
        size{0}
    {
        std::cout<<"Vector initialized\n";
    }
    
    // Copy constructor, copy everything from the other object?
    LLMVector(const LLMVector& other) {
        size = other.getSize();
        capacity = other.getCapacity();
        data = new T[capacity];
        for(size_t i=0; i<size; i++) {
            *(data+i) = other.at(i);
        }
    }
    
    // A destructor - delete the data while deleting the object
    ~LLMVector() {
        delete[] data;
        size = 0;
        capacity = 0;
    }
    
    // Assuming this builds an alias to other
    LLMVector& operator=(const LLMVector& other) {
        // Delete the current data of the object
        delete[] data;
        size = other.getSize();
        capacity = other.getCapacity();
        data = new T[size];
        for(size_t i=0; i<other.getSize(); i++) {
            // Not a shallow copy
            *(data+i) = other.at(i);
        }
        // What does this mean?
        return *this;
        
    }
    
    size_t getSize() const {
        return size;
    }
    
    // Didn't have to return a const because size_t is a single value and return by value wouldn't affect its performance much
    size_t getCapacity() const {
        return capacity;
    }
    
    const T* getData() const {
        return data;
    }
    
    // Get the value at index
    T at(size_t index) const {
        if (index >= size) {
            // Throw exception
            std::cout << "Index can't be greater than size\n";
        }
        return *(data+index);
    }
    
    void push_back(T elem) {
        if (size == capacity) {
            // Create new memory block with increased capacity &
            // copy the elements from the older data array to newer
            // one, delete the older elements & assign the newer one to the older one
            
            std::cout<<"MAX CAPACITY REACHED, ADDING MORE CAPACITY\n";
            T* new_data = new T[capacity + 10];
            for(size_t i=0; i<size; i++) {
                *(new_data+i) = *(data+i);
            }
            capacity += 10;
            delete[] data;
            data = new_data;
        }
        *(data + size) = elem;
        size += 1;
    }
protected:
private:
    T *data;
    size_t capacity;
    size_t size;

};

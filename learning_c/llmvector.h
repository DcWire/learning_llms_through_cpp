//
//  vector.h
//  learning_c
//
//  Created by Mohammed Anas Ali on 14/06/25.
//

#ifndef LLMVECTOR_H
#define LLMVECTOR_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <algorithm>

template <typename T>
class LLMVector {
private:
    T* data; // Pointer to dynamically allocated array
    size_t capacity; // Total allocated capacity
    size_t size; // Current number of elements

public:
    explicit LLMVector(size_t initialCapacity = 10)
    : data{initialCapacity > 0 ? new T[initialCapacity] : nullptr},
    capacity(initialCapacity),
    size(0)
    {

    }

    ~LLMVector() {
        
        if (data != nullptr)
            delete[] data;
        data = nullptr;
        
        size = 0;
        capacity = 0;
        
    }

    LLMVector(const LLMVector& other)
    : data{other.capacity > 0 ? new T[other.capacity] : nullptr},
    capacity{other.capacity},
    size{other.size}
    {
        // Deep copy. This is slow.
        for(size_t i=0; i<size; i++) {
            data[i] = other.data[i];
        }
    }

    LLMVector& operator=(const LLMVector& other) {
        if (this == &other) {
            return *this;
        }
        
        
        // Delete the data owned by the current vector
        if (data != nullptr)
            delete[] data;
        
        // Lets not do a shallow copy which leads to memory issues when the object is being deleted
//        data = other.data;
        capacity = other.capacity;
        size = other.size;
        
        
        if(capacity > 0) {
            data = new T[capacity];
            
            for(size_t i=0; i<size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
        
        return *this;

        

        return *this;
    }

    void push_back(const T& value) {
        if(size >= capacity) {
            // Increase capacity exponentially
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
            reserve(newCapacity);
        }

        data[size] = value;
        ++size;
    }


    // TODO: Whats the difference between this and the const version
    T& at(size_t index) {
        if(index >= size) {
            // Index cant be greater than size
            throw std::out_of_range("LLMVector::at: index " + std::to_string(index) + " out of range (size: " + std::to_string(size) + ")\n");
        }

        // Return a reference to the element
        return data[index];
    }

    const T& at(size_t index) const {
        if(index >= size) {
            // Index cant be greater than size
            throw std::out_of_range("LLMVector::at: index " + std::to_string(index) + " out of range (size: " + std::to_string(size) + ")\n");
        }

        // Return a reference to the element
        return data[index];
    }


    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    void reserve(size_t newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }

        // New memory allocated
        T* newData = new T[newCapacity];

        // Copy existing elements
        for (size_t i=0; i<size; ++i) {
            newData[i] = std::move(data[i]);
        }

        // Clean up old memory & update
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        size = 0;
    }

    T* data_ptr() {
        return data;
    }

    const T* data_ptr() const {
        return data;
    }

    T& operator[](size_t index) {
        // Faster than LLMVector::at
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }
};

#endif // LLMVECTOR_H

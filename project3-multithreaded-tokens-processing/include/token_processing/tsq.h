#ifndef TSQ_H
#define TSQ_H

#include<iostream>
#include<condition_variable>
#include<mutex>
#include<atomic>
#include<queue>
#include<functional>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable condition;
    std::atomic<bool> terminate{false};

public:
    void enqueue(T item);
    std::optional<T> dequeue();
    void stop();
    bool empty() const;
};
#endif

#include"token_processing/llminferenceengine.h"
#include"token_processing/tsq.h"

#include<iostream>
#include <mutex>


template<typename T>
void ThreadSafeQueue<T>::enqueue(T item) {

    {
        // Why is this in a separate scope?
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(item));
    }

    // Let dequeue start processing
    condition.notify_one();
}

template<typename T>
std::optional<T> ThreadSafeQueue<T>::dequeue() {
    std::unique_lock<std::mutex> lock(mutex);

    // TODO: What's going on here?
    condition.wait(lock, [this] {
       return !queue.empty() || terminate.load();
    });

    // TODO: What are these conditions?
    if (terminate.load() && queue.empty()) {
        return std::nullopt; // No more empty or stopped?
    }

    // Efficiently move the item from the queue
    T item = std::move(queue.front());
    queue.pop();
    return item;
}

// TODO: Signal to stop processing? Or is it to stop adding to the queue?
template<typename T>
void ThreadSafeQueue<T>::stop() {
    terminate.store(true);
    condition.notify_all();
}

// Check if queue is empty
template<typename T>
bool ThreadSafeQueue<T>::empty() const {
    // TODO: Why are we locking here?
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
}

LLMInferenceEngine::LLMInferenceEngine(int num_threads) {
    for (int i=0; i<num_threads; i++) {
        worker_threads.emplace_back(&LLMInferenceEngine::worker_loop, i);
    }
}

LLMInferenceEngine::~LLMInferenceEngine() {
    // TODO: Stop all threads
    work_queue.stop();
    for(auto &i: worker_threads) {
        if (i.joinable()) {
            i.join();
        }
    }
}

void LLMInferenceEngine::submit(const std::vector<std::string>& token_batch) {
    work_queue.enqueue(token_batch);
}

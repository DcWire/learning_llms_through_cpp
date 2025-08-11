#ifndef LLMINFERENCEENGINE_H
#define LLMINFERENCEENGINE_H

#include<iostream>
#include<thread>
#include<vector>
#include<string>
#include<atomic>
#include"tsq.h"

class LLMInferenceEngine {
private:
    ThreadSafeQueue<std::vector<std::string>> work_queue;
    std::vector<std::thread> worker_threads;
    std::atomic<bool> should_terminate{false};

    // Simulated LLM token processing function
    void process_token_batch(const std::vector<std::string>& batch, int thread_id) {
        std::cout << "Thread " << thread_id << " processing " << batch.size() << " tokens\n";
        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * batch.size()));
    }

    void worker_loop(int id) {
        while (true) {
            auto batch = work_queue.dequeue();
            if (!batch.has_value()) {
                break;
            }
            process_token_batch(*batch, id);
        }
    }
public:
    LLMInferenceEngine(int num_threads);
    ~LLMInferenceEngine();
    void submit(const std::vector<std::string>& token_batch);
};



#endif

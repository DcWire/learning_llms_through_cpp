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

public:
    LLMInferenceEngine(int num_threads);
    ~LLMInferenceEngine();
    void submit(const std::vector<std::string>& token_batch);
};



#endif

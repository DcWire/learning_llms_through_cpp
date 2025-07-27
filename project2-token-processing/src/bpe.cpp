// #include "token_processing/bpe.h"
#include "token_processing/bpe.h"
// #include "bpe.h"
#include<vector>
// #include<utility>
// #include<unordered_map>
// #include<string>
#include <iostream>


BytePairAlgorithm::BytePairAlgorithm(int vocab_size) {
    this->vocab_size = vocab_size;
}

std::vector<std::string> BytePairAlgorithm::tokenize(const std::string& text) {
    std::cout << "Converting to strings" << std::endl;
    std::cout<< this->vocab_size <<std::endl;
    return {};
}

std::string BytePairAlgorithm::detokenize(const std::vector<std::string>& tokens) {
    // TODO: Implement detokenization
    return "";
}

void BytePairAlgorithm::train(const std::vector<std::string>& corpus) {
    // TODO: Implement training logic
}

std::string BytePairAlgorithm::get_algorithm_name() const {
    return "Byte Pair Encoding";
}

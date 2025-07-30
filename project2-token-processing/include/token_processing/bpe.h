#ifndef BPE_H
#define BPE_H
#include "token_processing/tokenizer.h"
#include<string>
#include<vector>
#include<unordered_map>
#include<utility>
#include<map>
#include<cstring>

class BytePairAlgorithm : public TokenizerAlgorithm {
public:
    BytePairAlgorithm(int vocab_size);

    std::vector<std::string> tokenize(const std::string& text) override;
    std::string detokenize(const std::vector<std::string>& tokens) override;
    void train(const std::vector<std::string>& corpus) override;
    std::string get_algorithm_name() const override;
    std::vector<std::string> split(std::string s, const char& ch);
    std::string get_max_pair(std::vector<std::vector<std::string>>&, std::unordered_map<int, int>&);

private:
    std::unordered_map<std::string, int> vocab;
    std::vector<std::pair<std::string, std::string>> merges;
    int vocab_size;
};

#endif

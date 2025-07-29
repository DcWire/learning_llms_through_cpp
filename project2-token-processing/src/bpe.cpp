#include "token_processing/bpe.h"
// #include "bpe.h"
#include <algorithm>
#include <cctype>
#include<vector>
// #include<utility>
// #include<unordered_map>
#include<string>
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
    std::unordered_map<std::string, int> count;
    std::vector<std::vector<std::string>> words;

    for(int i=0; i<corpus.size(); i++) {
        // Can optimize this further by just initializing a single vector object
        std::vector<std::string> split_sentence = this->split(corpus[i], ' ');

        for(int k=0; k<split_sentence.size(); k++) {
            count[split_sentence[k]]++;
        }
    }

    for(auto &i: count) {
        std::vector<std::string> vec(i.first.length() + 1, "");
        for(int j=0; j<i.first.length(); j++) {
            vec[j] = i.first[j];
        }
        vec[i.first.length()] = "</w>";
        words.push_back(vec);
    }

    // for(int i=0; i<words.size(); i++) {
    //     for(int j=0; j<words[i].size(); j++) {
    //         std::cout<< words[i][j] << " ";
    //     }
    //     std::cout<< std::endl;
    // }



    std::cout<<count.size()<<std::endl;
}


std::string BytePairAlgorithm::get_algorithm_name() const {
    return "Byte Pair Encoding";
}

std::vector<std::string> BytePairAlgorithm::split(std::string s, const char& ch) {

    std::vector<std::string> ans;
    std::string temp = "";

    for(int i=0; i<s.length(); i++) {
        if(s[i] == ch) {
            if(temp.length() != 0) {
                ans.push_back(temp);
                temp = "";
            }
        } else {
            temp += s[i];
        }
    }

    if (temp.length() != 0) {
        ans.push_back(temp);
    }
    return ans;
}

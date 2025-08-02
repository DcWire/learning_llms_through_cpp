#include "token_processing/bpe.h"
#include <iostream>
#include <stdexcept>


BytePairAlgorithm::BytePairAlgorithm(int vocab_size) {
    this->vocab_size = vocab_size;
}

std::vector<std::string> BytePairAlgorithm::tokenize(const std::string& text) {
    if (this->vocab.size() == 0) {
        throw std::runtime_error("Training has probably not be run yet. Vocab size is 0");
    }
    std::vector<std::string> split_text = this->split(text, ' ');
    std::vector<std::string> results;

    for(int i=0; i<split_text.size(); i++) {
        std::string s = "";
        // A flag to see if the word exists in the vocabulary
        // TODO: This isn't right... need to apply merge rules on  each token
        int count = 0;
        std::vector<std::string> tokenized_text;
        for(int j=0; j<split_text[i].length(); j++) {
            tokenized_text.push_back(std::string(1, split_text[i][j]));
        }
        tokenized_text.push_back("</w>");


        for(int j=0; j<this->merges.size(); j++) {
            std::vector<std::string> tokenized_text_temp;
            for(int k=0; k<tokenized_text.size(); k++) {
                if((k<tokenized_text.size()-1) && (tokenized_text[k]+tokenized_text[k+1] == this->merges[j])) {
                    tokenized_text_temp.push_back(tokenized_text[k]+tokenized_text[k+1]);
                    k++;
                } else {
                    tokenized_text_temp.push_back(tokenized_text[k]);
                }
            }
            tokenized_text = tokenized_text_temp;
        }

        for(int j=0; j<tokenized_text.size(); j++) {
            results.push_back(tokenized_text[j]);
        }
    }
    return results;
}

std::string BytePairAlgorithm::detokenize(const std::vector<std::string>& tokens) {

    std::string s = "";
    std::string result = "";
    for(int i=0; i<tokens.size(); i++) {
        int j = 0;
        while(j < tokens[i].length()) {
            if(tokens[i][j] == '<') {
                result += s;
                s = "";

                if(i != tokens.size() - 1) {
                    result += " ";
                }
                break;
            }
            s += tokens[i][j];
            j++;
        }
    }

    return result;
}

void BytePairAlgorithm::train(const std::vector<std::string>& corpus) {
    // Store count of words
    std::unordered_map<std::string, int> count;
    // Map words with index for now, can optimize
    std::unordered_map<int, int> words_map;

    int counter = 0;
    // Store words
    std::vector<std::vector<std::string>> words;

    int num_merges = 10;
    std::vector<std::string> merges(num_merges);

    for(int i=0; i<corpus.size(); i++) {
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

        words_map[counter] = i.second;
        ++counter;
    }

    // Run k times and perform a number of merges
    for(int k=0; k<num_merges; k++) {
        std::string max_pair = this->get_max_pair(words, words_map);
        std::vector<std::vector<std::string>> new_words;

        for(int i=0; i<words.size(); i++) {
            std::vector<std::string> vec;
            for(int j=0; j<words[i].size(); j++) {
                if ((j < words[i].size() - 1) && (words[i][j]+words[i][j+1] == max_pair)) {
                    vec.push_back(max_pair);
                    j++;
                } else {
                    vec.push_back(words[i][j]);
                }
            }
            new_words.push_back(vec);
        }

        words = new_words;
        merges[k] = max_pair;
    }

    this->merges = merges;

    // Write vocabulary
    this->vocab.clear();

    int token_id = 0;

    for(const auto& word: words) {
        for(const auto& token: word) {
            if(this->vocab.find(token) == this->vocab.end()) {
                this->vocab[token] = token_id++;
            }
        }
    }


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

std::string BytePairAlgorithm::get_max_pair(std::vector<std::vector<std::string>>& words, std::unordered_map<int, int>& words_map) {
    std::map<std::pair<std::string, std::string>, int> count;

    for(int i=0; i<words.size(); i++) {
        for(int j=0; j<words[i].size()-1; j++) {
            count[{words[i][j], words[i][j+1]}]+=words_map[i];
        }
    }
    int mx = 0;
    std::string max_pair;
    for(auto &i: count) {
        if(i.second > mx) {
            mx = i.second;
            max_pair = i.first.first + i.first.second;
        }
    }

    return max_pair;
}

// #include<iostream>
#include<vector>
#include<string>

#ifndef TOKEN_ALGORITHM_H
#define TOKEN_ALGORITHM_H
class TokenizerAlgorithm {
    public:
        virtual ~TokenizerAlgorithm() = default;
        virtual std::vector<std::string> tokenize(const std::string& text) = 0;
        virtual std::string detokenize(const std::vector<std::string>& tokens) = 0;
        virtual void train(const std::vector<std::string>& corpus) = 0;
        virtual std::string get_algorithm_name() const = 0;
};
#endif

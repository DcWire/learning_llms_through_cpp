#include<iostream>
#include"../include/token_processing/bpe.h"

int main() {
    BytePairAlgorithm tokenizer(100);
    tokenizer.train(
        {
            "My name is Anas and I",
            "I love playing football",
            "I I I I"
        }
    );

    std::vector<std::string> results = tokenizer.tokenize("My name is Anas and I");


    std::cout << "After tokenization: \n";
    for(int i=0; i<results.size(); i++) {
        std::cout << results[i] << " ";
    }

    std::cout << "\n\n";

    std::string detokenized_results = tokenizer.detokenize(results);
    std::cout << "Detokenized: \n" << detokenized_results;

    return 0;
}

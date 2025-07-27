#include<iostream>
#include"../include/token_processing/bpe.h"

int main() {
    std::cout<<"ITS HAPPENING"<<std::endl;
    BytePairAlgorithm tokenizer(100);
    tokenizer.tokenize("meow meowo");
    return 0;
}

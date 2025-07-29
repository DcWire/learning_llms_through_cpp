#include<iostream>
#include"../include/token_processing/bpe.h"

int main() {
    BytePairAlgorithm tokenizer(100);
    tokenizer.train(
        {
            "My name is Anas",
            "I love playing football"
        }
    );
    return 0;
}

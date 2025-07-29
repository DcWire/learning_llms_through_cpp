#include<iostream>
#include"../include/token_processing/bpe.h"

int main() {
    BytePairAlgorithm tokenizer(100);
    tokenizer.train(
        {
            "My name is Anas and I",
            "I love playing football"
        }
    );
    return 0;
}

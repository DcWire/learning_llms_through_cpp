#include"token_processing/llminferenceengine.h"

int main() {
    LLMInferenceEngine engine(3);

    // Submit tasks to be finished
    engine.submit({"Hello", "world"});
    engine.submit({"This", "is", "a", "test"});
    engine.submit({"Goodbye"});
    engine.submit({"More", "tokens", "for", "processing"});

    // Wait for destructor to be called
    return 0;
}

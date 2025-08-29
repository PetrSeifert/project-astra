#include <iostream>
#include <nlohmann/json.hpp>

// Stub wrapper for whisper.cpp STT service.
int main() {
    nlohmann::json request;
    if (!(std::cin >> request)) {
        return 1;
    }
    // TODO: Implement whisper.cpp inference
    nlohmann::json response = {
        {"text", "stub transcription"}
    };
    std::cout << response.dump();
    return 0;
}

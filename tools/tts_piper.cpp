#include <iostream>
#include <nlohmann/json.hpp>

// Stub wrapper for Piper TTS service.
int main() {
    nlohmann::json request;
    if (!(std::cin >> request)) {
        return 1;
    }
    // TODO: Implement Piper TTS inference
    nlohmann::json response = {
        {"audio", "base64_pcm_stub"}
    };
    std::cout << response.dump();
    return 0;
}

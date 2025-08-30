#include <cstdio>
#include <iostream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

int main() {
    spdlog::info("orchestrator_brain starting (stdio JSON)");
    std::string payload;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        payload += buffer;
    }
    if (payload.empty()) {
        nlohmann::json resp = {{"tool", "say"}, {"args", {{"text", ""}}}};
        std::cout << resp.dump();
        return 0;
    }

    nlohmann::json req = nlohmann::json::parse(payload, nullptr, false);
    if (req.is_discarded()) {
        spdlog::error("Invalid JSON input to brain");
        return 1;
    }

    std::string text = req.value("utterance", nlohmann::json{}).value("text", "");
    if (text.empty()) {
        nlohmann::json resp = {{"tool", "say"}, {"args", {{"text", ""}}}};
        std::cout << resp.dump();
        return 0;
    }

    nlohmann::json resp = {
        {"tool", "say"},
        {"args", {{"text", std::string("You said: ") + text}}}
    };
    std::cout << resp.dump();
    return 0;
}



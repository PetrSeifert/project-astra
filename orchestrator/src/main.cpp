#include <cstdlib>
#include <iostream>

#include "discord_bot.hpp"
#include "tool_registry.hpp"
#include "tool_interface.hpp"

/**
 * @brief Simple ProcessTool that spawns a process per call and communicates over stdio.
 */
class ProcessTool : public ITool {
public:
    explicit ProcessTool(std::string exec_path) : exec_path_(std::move(exec_path)) {}

    nlohmann::json call(const nlohmann::json& request) override {
        // Very naive implementation using popen
        std::string cmd = exec_path_;
#ifdef _WIN32
        FILE* pipe = _popen(cmd.c_str(), "w+");
#else
        FILE* pipe = popen(cmd.c_str(), "w+");
#endif
        if (!pipe) {
            return nlohmann::json{{"error", "spawn_failed"}};
        }
        std::string req = request.dump();
        fwrite(req.data(), 1, req.size(), pipe);
        fflush(pipe);

        char buffer[4096];
        std::string response;
        while (fgets(buffer, sizeof(buffer), pipe)) {
            response += buffer;
        }
#ifdef _WIN32
        _pclose(pipe);
#else
        pclose(pipe);
#endif
        if (response.empty()) {
            return nlohmann::json{};
        }
        return nlohmann::json::parse(response, nullptr, false);
    }

private:
    std::string exec_path_;
};

int main() {
    const char* token = std::getenv("DISCORD_TOKEN");
    if (!token) {
        std::cerr << "DISCORD_TOKEN env var not set" << std::endl;
        return 1;
    }

    ToolRegistry registry;
    registry.register_tool("stt", std::make_shared<ProcessTool>("./stt_whisper"));
    registry.register_tool("llm", std::make_shared<ProcessTool>("./llm_llama"));
    registry.register_tool("tts", std::make_shared<ProcessTool>("./tts_piper"));

    DiscordBot bot(token, registry);
    bot.run();
    return 0;
}

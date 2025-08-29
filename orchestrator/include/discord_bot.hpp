#pragma once

#include <dpp/dpp.h>
#include <unordered_map>
#include "tool_registry.hpp"
#include "pipeline.hpp"

/**
 * @brief Discord bot orchestrating text and voice interactions.
 */
class DiscordBot {
public:
    DiscordBot(const std::string& token, ToolRegistry& registry);

    void run();

private:
    dpp::cluster bot_;
    ToolRegistry& registry_;
    PipelineManager pipelines_;
    std::unordered_map<uint32_t, dpp::snowflake> ssrc_to_user_;

    void setup_handlers();
};

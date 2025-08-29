#pragma once

#include "pipeline.hpp"
#include "tool_registry.hpp"
#include <dpp/dpp.h>
#include <unordered_map>

/**
 * @brief Discord bot orchestrating text and voice interactions.
 */
class DiscordBot {
public:
  DiscordBot(const std::string &token, uint32_t intents,
             ToolRegistry &registry);

  void run();

private:
  dpp::cluster bot_;
  ToolRegistry &registry_;
  PipelineManager pipelines_;

  void setup_handlers();
};

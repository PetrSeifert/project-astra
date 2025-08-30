#include <cstdlib>
#include <memory>
#include <spdlog/spdlog.h>

#include "discord_bot.hpp"

int main() {
    const char *token = std::getenv("DISCORD_TOKEN");
    const uint32_t intents = dpp::i_default_intents | dpp::i_message_content |
                             dpp::i_guild_messages | dpp::i_direct_messages |
                             dpp::i_guild_voice_states;
    if (!token) {
        spdlog::error("DISCORD_TOKEN env var not set");
        return 1;
    }

    DiscordBot bot(token, intents);
    spdlog::info("Starting Discord bot");
    bot.run();
    spdlog::info("Discord bot stopped");
    return 0;
}



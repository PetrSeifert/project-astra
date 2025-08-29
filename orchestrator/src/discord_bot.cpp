#include "discord_bot.hpp"

#include <iostream>

DiscordBot::DiscordBot(const std::string& token, uint32_t intents, ToolRegistry& registry)
    : bot_(token, intents), registry_(registry), pipelines_(registry_) {
    setup_handlers();
}

void DiscordBot::setup_handlers() {
    bot_.on_log(dpp::utility::cout_logger());

    bot_.on_message_create([this](const dpp::message_create_t& event) {
        if (event.msg.author.is_bot()) {
            return;
        }
        // Echo text messages for now
        bot_.message_create(dpp::message(event.msg.channel_id, event.msg.content));
    });

    bot_.on_voice_receive([this](const dpp::voice_receive_t& event) {
        std::vector<int16_t> pcm; // TODO: decode Opus frame to PCM
        auto voice_client = event.voice_client;
        if (!voice_client) {
            return;
        }
        auto send_audio = [voice_client](const std::vector<int16_t>& pcm_out) {
            // TODO: encode to Opus and send via voice_client->send_audio_raw
            (void)pcm_out;
        };
        pipelines_.on_audio_chunk(std::to_string(event.user_id), pcm, send_audio);
    });
}

void DiscordBot::run() {
    bot_.start(dpp::st_wait);
}
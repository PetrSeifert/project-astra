#include "message_module.hpp"
#include "discord_bot.hpp"

MessageModule::MessageModule(DiscordBot &bot) : bot_(bot) {
  bot_.bot().on_message_create([this](const dpp::message_create_t &event) {
    if (event.msg.author.is_bot())
      return;
    bot_.bot().message_create(
        dpp::message(event.msg.channel_id, event.msg.content));
  });
}

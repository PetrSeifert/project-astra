#include "voice_module.hpp"
#include "commands_module.hpp"
#include "discord_bot.hpp"

VoiceModule::VoiceModule(DiscordBot &bot, CommandsModule &commands)
    : bot_(bot), commands_(commands) {
  dpp::slashcommand cmd("joinvoice", "Join your voice channel",
                        bot_.bot().me.id);
  commands_.addCommand(std::move(cmd));

  commands_.addCommandHandler(
      "joinvoice", [this](const dpp::slashcommand_t &event) {
        dpp::snowflake guild_id = event.command.guild_id;
        dpp::guild *g = dpp::find_guild(guild_id);
        if (!g) {
          event.reply(dpp::ir_channel_message_with_source,
                      dpp::message("Cannot find guild context.")
                          .set_flags(dpp::m_ephemeral));
          return;
        }

        dpp::snowflake user_id = event.command.get_issuing_user().id;
        bool connected = g->connect_member_voice(bot_.bot(), user_id);
        if (!connected) {
          event.reply(
              dpp::ir_channel_message_with_source,
              dpp::message(
                  "You are not in a voice channel or I lack permissions.")
                  .set_flags(dpp::m_ephemeral));
          return;
        }

        event.reply(dpp::ir_channel_message_with_source,
                    dpp::message("Joining your voice channel...")
                        .set_flags(dpp::m_ephemeral));
      });
}

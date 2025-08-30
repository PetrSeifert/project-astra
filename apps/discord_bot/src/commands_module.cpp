#include "commands_module.hpp"
#include "discord_bot.hpp"

#include <spdlog/spdlog.h>

CommandsModule::CommandsModule(DiscordBot &bot) : bot_(bot) {
  bot_.bot().on_slashcommand(
      [this](const dpp::slashcommand_t &event) { handleSlashCommand(event); });
}

void CommandsModule::addCommand(dpp::slashcommand &&command) {
  pending_commands_.push_back(std::move(command));
}

void CommandsModule::addCommandHandler(const std::string &command_name,
                                       SlashHandler handler) {
  command_handlers_[command_name] = std::move(handler);
}

void CommandsModule::registerCommands() {
  if (pending_commands_.empty())
    return;

  bot_.bot().global_bulk_command_create(
      pending_commands_, [this](const dpp::confirmation_callback_t &cb) {
        if (cb.is_error()) {
          spdlog::error("Error registering commands: {}",
                        cb.get_error().message);
        } else {
          spdlog::info("Successfully registered {} slash commands.",
                       pending_commands_.size());
        }
      });
}

void CommandsModule::handleSlashCommand(const dpp::slashcommand_t &event) {
  const std::string &name = event.command.get_command_name();
  auto it = command_handlers_.find(name);
  if (it != command_handlers_.end())
    it->second(event);
  else
    spdlog::warn("Received unknown command: {}", name);
}



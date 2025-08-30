#pragma once

#include <dpp/dpp.h>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class DiscordBot;

class CommandsModule {
public:
  explicit CommandsModule(DiscordBot &bot);

  using SlashHandler = std::function<void(const dpp::slashcommand_t &)>;

  void addCommand(dpp::slashcommand &&command);
  void addCommandHandler(const std::string &command_name, SlashHandler handler);
  void registerCommands();
  void handleSlashCommand(const dpp::slashcommand_t &event);

private:
  DiscordBot &bot_;
  std::vector<dpp::slashcommand> pending_commands_;
  std::unordered_map<std::string, SlashHandler> command_handlers_;
};

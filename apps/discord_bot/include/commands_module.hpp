#pragma once

#include <dpp/dpp.h>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class DiscordBot;

class CommandsModule {
public:
  using SlashHandler = std::function<void(const dpp::slashcommand_t &)>;

  explicit CommandsModule(DiscordBot &bot);

  void addCommand(dpp::slashcommand &&command);
  void addCommandHandler(const std::string &command_name, SlashHandler handler);
  void registerCommands();

private:
  DiscordBot &bot_;
  std::vector<dpp::slashcommand> pending_commands_;
  std::unordered_map<std::string, SlashHandler> command_handlers_;
  void handleSlashCommand(const dpp::slashcommand_t &event);
};



#pragma once

#include <dpp/dpp.h>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class CommandsModule;
class VoiceModule;
class MessageModule;

class DiscordBot {
public:
  DiscordBot(const std::string &token, uint32_t intents);
  ~DiscordBot();

  void run();

  using SlashCommandHandler = std::function<void(const dpp::interaction_create_t &)>;

  void register_command(const std::string &name, const std::string &description,
                        SlashCommandHandler handler,
                        const std::vector<dpp::command_option> &options = {});

  dpp::cluster &bot() { return bot_; }

private:
  dpp::cluster bot_;

  struct PendingCommand {
    std::string name;
    std::string description;
    std::vector<dpp::command_option> options;
    SlashCommandHandler handler;
  };

  std::vector<PendingCommand> pending_commands_;
  std::unordered_map<std::string, SlashCommandHandler> command_handlers_;

  std::unique_ptr<CommandsModule> commands_module_;
  std::unique_ptr<VoiceModule> voice_module_;
  std::unique_ptr<MessageModule> message_module_;

  void setup_handlers();
};



#pragma once

#include <dpp/dpp.h>

class DiscordBot;
class CommandsModule;

class VoiceModule {
public:
  VoiceModule(DiscordBot &bot, CommandsModule &commands);

private:
  DiscordBot &bot_;
  CommandsModule &commands_;
};

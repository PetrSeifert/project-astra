#pragma once

#include <dpp/dpp.h>

class DiscordBot;

class MessageModule {
public:
  explicit MessageModule(DiscordBot &bot);

private:
  DiscordBot &bot_;
};

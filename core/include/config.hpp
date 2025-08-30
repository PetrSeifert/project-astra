#pragma once
#include "logging.hpp"

#include <string>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <cctype>

namespace config {
    inline std::string getEnvVar(const char* name, const char* defaultValue = "") {
        const char* value = std::getenv(name);
        if (value == nullptr) {
            LOG_WARN("Environment variable {} not found. Using default value: {}", name, defaultValue);
            value = defaultValue;
        }
    
        return value;
    }

    inline uint64_t getEnvVarUInt64(const char* name, uint64_t defaultValue = 0) {
        const char* value = std::getenv(name);
        if (value == nullptr) {
            LOG_WARN("Environment variable {} not found. Using default value: {}", name, defaultValue);
            return defaultValue;
        }

        try {
            return std::stoull(value);
        } catch (...) {
            LOG_ERROR("Environment variable {} is not a valid unsigned long long. Using default value: {}", name, defaultValue);
            return defaultValue;
        }
    }

    const std::string DISCORD_TOKEN = getEnvVar("DISCORD_TOKEN");

    const std::string MODEL_NAME = getEnvVar("MODEL_NAME", "qwen2.5-7b-instruct");
    
    const std::string LLM_HOST = getEnvVar("LLM_HOST", "localhost");
    const uint64_t LLM_PORT = getEnvVarUInt64("LLM_PORT", 8000);

    // The Discord channel ID where the bot will send boot messages
    const uint64_t DEFAULT_CHANNEL_ID = getEnvVarUInt64("DEFAULT_CHANNEL_ID", 0);

    // Whisper STT Configuration
    const std::string WHISPER_MODEL_NAME = getEnvVar("WHISPER_MODEL_NAME", "ggml-large-v3-turbo-q8_0.bin");
    
    // Whisper Service Configuration
    const std::string WHISPER_SERVICE_HOST = getEnvVar("WHISPER_SERVICE_HOST", "0.0.0.0");
    const uint64_t WHISPER_SERVICE_PORT = getEnvVarUInt64("WHISPER_SERVICE_PORT", 8001);
} 
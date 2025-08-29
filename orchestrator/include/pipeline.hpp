#pragma once

#include "tool_registry.hpp"
#include <functional>
#include <mutex>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>

/** Utterance JSON structure. */
struct Utterance {
  std::string user_id;
  double t0;
  double t1;
  std::string text;
};

/**
 * @brief Per-user processing pipeline.
 */
class UserPipeline {
public:
  UserPipeline(ToolRegistry &registry,
               std::function<void(const std::vector<int16_t> &)> send_audio);

  void process_audio(const std::vector<int16_t> &pcm,
                     const std::string &user_id);

private:
  ToolRegistry &registry_;
  std::function<void(const std::vector<int16_t> &)> send_audio_;
};

/**
 * @brief Manages pipelines for all users.
 */
class PipelineManager {
public:
  explicit PipelineManager(ToolRegistry &registry);

  void
  on_audio_chunk(const std::string &user_id, const std::vector<int16_t> &pcm,
                 std::function<void(const std::vector<int16_t> &)> send_audio);

private:
  ToolRegistry &registry_;
  std::unordered_map<std::string, std::unique_ptr<UserPipeline>> pipelines_;
  std::mutex mutex_;
};

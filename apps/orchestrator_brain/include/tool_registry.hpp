#pragma once

#include "tool_interface.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

/**
 * @brief Registry of available tools.
 */
class ToolRegistry {
public:
  /** Register a tool by name. */
  void register_tool(const std::string &name, std::shared_ptr<ITool> tool);

  /** Call a registered tool. */
  nlohmann::json call(const std::string &name, const nlohmann::json &request);

private:
  std::unordered_map<std::string, std::shared_ptr<ITool>> tools_;
};

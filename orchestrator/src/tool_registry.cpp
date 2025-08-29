#include "tool_registry.hpp"

#include <spdlog/spdlog.h>

void ToolRegistry::register_tool(const std::string& name,
                                 std::shared_ptr<ITool> tool) {
  tools_[name] = std::move(tool);
}

nlohmann::json ToolRegistry::call(const std::string& name,
                                  const nlohmann::json& request) {
  auto it = tools_.find(name);
  if (it == tools_.end()) {
    spdlog::error("Tool not found: {}", name);
    return nlohmann::json{{"error", "tool_not_found"}};
  }
  auto& tool = it->second;
  nlohmann::json response = tool->call(request);
  spdlog::info("[ToolRegistry] {} <= {}", name, request.dump());
  spdlog::info("[ToolRegistry] {} => {}", name, response.dump());
  return response;
}
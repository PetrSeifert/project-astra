#include "tool_registry.hpp"

#include <iostream>

void ToolRegistry::register_tool(const std::string& name, std::shared_ptr<ITool> tool) {
    tools_[name] = std::move(tool);
}

nlohmann::json ToolRegistry::call(const std::string& name, const nlohmann::json& request) {
    auto it = tools_.find(name);
    if (it == tools_.end()) {
        std::cerr << "Tool not found: " << name << std::endl;
        return nlohmann::json{ {"error", "tool_not_found"} };
    }
    auto& tool = it->second;
    nlohmann::json response = tool->call(request);
    // Log tool call
    std::cout << "[ToolRegistry] " << name << " <= " << request.dump() << std::endl;
    std::cout << "[ToolRegistry] " << name << " => " << response.dump() << std::endl;
    return response;
}
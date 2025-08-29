#pragma once

#include <nlohmann/json.hpp>

/**
 * @brief Interface for tools callable via the ToolRegistry.
 */
class ITool {
public:
    virtual ~ITool() = default;

    /**
     * @brief Call the tool with a JSON request.
     * @param request JSON arguments.
     * @return JSON response.
     */
    virtual nlohmann::json call(const nlohmann::json& request) = 0;
};

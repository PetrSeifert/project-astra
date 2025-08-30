cmake_minimum_required(VERSION 3.20)

add_executable(orchestrator_brain
    src/brain_main.cpp
    src/tool_registry.cpp
)

target_include_directories(orchestrator_brain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(orchestrator_brain PRIVATE nlohmann_json::nlohmann_json spdlog::spdlog)

# Place binaries together so the bot can spawn the brain by relative path
set_target_properties(orchestrator_brain PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)



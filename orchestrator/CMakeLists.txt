cmake_minimum_required(VERSION 3.20)
project(Orchestrator LANGUAGES CXX)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(dpp CONFIG QUIET)

add_library(orchestrator_lib
    src/tool_registry.cpp
    src/discord_bot.cpp
    src/pipeline.cpp
)

target_include_directories(orchestrator_lib PUBLIC include)

target_link_libraries(orchestrator_lib PUBLIC nlohmann_json::nlohmann_json)
if(dpp_FOUND)
    target_link_libraries(orchestrator_lib PUBLIC dpp)
else()
    message(WARNING "D++ library not found. Discord features will be disabled.")
endif()

add_executable(orchestrator src/main.cpp)

target_link_libraries(orchestrator PRIVATE orchestrator_lib)

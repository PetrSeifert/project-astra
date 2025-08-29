cmake_minimum_required(VERSION 3.20)
project(AstraAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/nlohmann_json EXCLUDE_FROM_ALL)
set(DPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(DPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/DPP EXCLUDE_FROM_ALL)

# Fetch spdlog from GitHub for robust logging
include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(spdlog)

add_subdirectory(orchestrator)
add_subdirectory(tools)
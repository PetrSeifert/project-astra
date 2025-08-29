cmake_minimum_required(VERSION 3.20)
project(Orchestrator LANGUAGES CXX)

add_library(orchestrator_lib STATIC
    src/tool_registry.cpp
    src/discord_bot.cpp
    src/pipeline.cpp
)

target_include_directories(orchestrator_lib PUBLIC include)

target_link_libraries(orchestrator_lib PUBLIC nlohmann_json::nlohmann_json spdlog::spdlog)
if(TARGET dpp)
    target_link_libraries(orchestrator_lib PUBLIC dpp)
else()
    message(WARNING "D++ library not found. Discord features will be disabled.")
endif()

add_executable(orchestrator src/main.cpp)

target_link_libraries(orchestrator PRIVATE orchestrator_lib)

# Copy all runtime DLLs (including third_party transitive ones) next to the executable
if(MSVC)
    add_custom_command(TARGET orchestrator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copy runtime DLLs for orchestrator"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:orchestrator>
            $<TARGET_FILE_DIR:orchestrator>
        COMMAND_EXPAND_LISTS
    )

    # Also copy any prebuilt DLLs bundled with DPP (e.g., zlib1.dll, opus.dll, etc.) if present
    set(DPP_WIN32_DLL_DIR "${CMAKE_SOURCE_DIR}/third_party/DPP/win32")
    add_custom_command(TARGET orchestrator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -Dsrc_dir="${DPP_WIN32_DLL_DIR}" -Ddst_dir="$<TARGET_FILE_DIR:orchestrator>" -P "${CMAKE_CURRENT_LIST_DIR}/copy_dpp_dlls.cmake"
    )
endif()
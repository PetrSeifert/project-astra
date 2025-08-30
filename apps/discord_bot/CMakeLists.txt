cmake_minimum_required(VERSION 3.20)

add_executable(discord_bot
    src/discord_main.cpp
    src/discord_bot.cpp
    src/commands_module.cpp
    src/voice_module.cpp
    src/message_module.cpp
)

target_include_directories(discord_bot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(discord_bot PUBLIC nlohmann_json::nlohmann_json spdlog::spdlog)
if(TARGET dpp)
    target_link_libraries(discord_bot PUBLIC dpp)
else()
    message(WARNING "D++ library not found. Discord features will be disabled.")
endif()

# Place binaries together so the bot can spawn the brain by relative path
set_target_properties(discord_bot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(MSVC)
    add_custom_command(TARGET discord_bot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copy runtime DLLs for discord_bot"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:discord_bot>
            $<TARGET_FILE_DIR:discord_bot>
        COMMAND_EXPAND_LISTS
    )

    # Also copy any prebuilt DLLs bundled with DPP (e.g., zlib1.dll, opus.dll, etc.) if present
    set(DPP_WIN32_DLL_DIR "${CMAKE_SOURCE_DIR}/third_party/DPP/win32")
    add_custom_command(TARGET discord_bot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -Dsrc_dir="${DPP_WIN32_DLL_DIR}" -Ddst_dir="$<TARGET_FILE_DIR:discord_bot>" -P "${CMAKE_CURRENT_LIST_DIR}/copy_dpp_dlls.cmake"
    )
endif()



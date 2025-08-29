cmake_minimum_required(VERSION 3.20)
project(Tools LANGUAGES CXX)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(stt_whisper stt_whisper.cpp)
target_link_libraries(stt_whisper PRIVATE nlohmann_json::nlohmann_json)

add_executable(tts_piper tts_piper.cpp)
target_link_libraries(tts_piper PRIVATE nlohmann_json::nlohmann_json)

add_executable(llm_llama llm_llama.cpp)
target_link_libraries(llm_llama PRIVATE nlohmann_json::nlohmann_json)

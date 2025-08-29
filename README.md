# Project Astra

Project Astra is a modular, local-first AI companion framework. The goal is to provide a low-latency assistant that can run fully on your own hardware while remaining easy to extend with new capabilities.

## Features
- **Discord integration** via [D++] allowing the bot to handle text and voice in guilds or DMs.
- **Tool-based architecture**: external microservices communicate with the orchestrator through JSON tool calls.
- **Audio pipeline**: voice data is streamed per-user through VAD → Whisper STT → Llama LLM → Piper TTS.
- **Extensibility**: new tools (e.g., `play_sfx`, `switch_scene`) can be added by implementing the `ITool` interface or running a sidecar process.

## Directory Layout
- `orchestrator/` – core C++ bot with tool registry and pipeline logic.
- `tools/` – standalone executables wrapping Whisper STT, Llama LLM, and Piper TTS.
- `third_party/` – git submodules for dependencies (D++, nlohmann_json, whisper.cpp, llama.cpp, piper).

## Build
1. Clone the repository and init submodules:
   ```bash
   git clone <repo> project-astra
   cd project-astra
   git submodule update --init --recursive
   ```
2. Configure and build using CMake:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```
3. Run the orchestrator (requires a Discord bot token in `DISCORD_TOKEN` env var):
   ```bash
   ./build/orchestrator/orchestrator
   ```

## Roadmap
- Full implementations for Whisper, Llama, and Piper bindings.
- Additional tools such as prosody control, OBS/VTube Studio integration, and web search.
- Enhanced conversation management and floor control.

## License
This project is released under the MIT License. See [LICENSE](LICENSE) for details.
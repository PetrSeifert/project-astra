#include "pipeline.hpp"

#include <iostream>

UserPipeline::UserPipeline(ToolRegistry& registry,
                           std::function<void(const std::vector<int16_t>&)> send_audio)
    : registry_(registry), send_audio_(std::move(send_audio)) {}

void UserPipeline::process_audio(const std::vector<int16_t>& /*pcm*/, const std::string& user_id) {
    // TODO: Implement VAD and buffering of PCM frames.
    nlohmann::json stt_req = { {"user_id", user_id}, {"audio", "TODO"} };
    nlohmann::json stt_resp = registry_.call("stt", stt_req);

    Utterance utt{user_id, 0.0, 0.0, stt_resp.value("text", "")};
    nlohmann::json llm_req = { {"utterance", { {"user_id", utt.user_id}, {"t0", utt.t0}, {"t1", utt.t1}, {"text", utt.text} }} };
    nlohmann::json llm_resp = registry_.call("llm", llm_req);

    if (llm_resp.value("tool", "") == "say") {
        nlohmann::json tts_resp = registry_.call("tts", llm_resp["args"]);
        // tts_resp expected to contain PCM16LE data in base64 or similar
        // For now, just log and ignore audio content
        std::vector<int16_t> pcm_out; // TODO: decode tts_resp
        send_audio_(pcm_out);
    }
}

PipelineManager::PipelineManager(ToolRegistry& registry)
    : registry_(registry) {}

void PipelineManager::on_audio_chunk(const std::string& user_id,
                                     const std::vector<int16_t>& pcm,
                                     std::function<void(const std::vector<int16_t>&)> send_audio) {
    std::unique_lock<std::mutex> lock(mutex_);
    auto& pipeline = pipelines_[user_id];
    if (!pipeline) {
        pipeline = std::make_unique<UserPipeline>(registry_, send_audio);
    }
    lock.unlock();
    pipeline->process_audio(pcm, user_id);
}
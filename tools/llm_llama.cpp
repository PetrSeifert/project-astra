#include <iostream>
#include <nlohmann/json.hpp>

// Stub wrapper for llama.cpp LLM service producing tool calls.
int main() {
  nlohmann::json request;
  if (!(std::cin >> request))
    return 1;
  // TODO: Implement llama.cpp inference with grammar-constrained JSON output
  nlohmann::json response = {
      {"tool", "say"},
      {"args", {{"text", "Hello world!"}, {"voice", "piper:en_US-amy"}}}};
  std::cout << response.dump();
  return 0;
}

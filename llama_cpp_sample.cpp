#include "llama.h"

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " model.gguf \"prompt text\"\n";
        return 1;
    }

    std::string model_path = argv[1];
    std::string prompt = argv[2];

    // 生成最大長
    int n_predict = 512;

    // **各パラメータ**
    int n_ctx     = 4096; // 総コンテキスト長
    int n_batch   = 2048; // 1回のdecodeで処理できるトークン数
    int n_ubatch  = 512;  // 内部マイクロバッチ（VRAM節約）
    int n_layer   = 36;   // GPUに載せる層数（-1 = すべての層）

    // GPUでoffloadする層数
    llama_model_params mparams = llama_model_default_params();
    mparams.n_gpu_layers = n_layer;

    // **モデルロード**
    llama_backend_init();
    ggml_backend_load_all();

    llama_model *model = llama_model_load_from_file(model_path.c_str(), mparams);
    if (!model) {
        std::cerr << "ERROR: failed to load model\n";
        return 1;
    }
    const llama_vocab *vocab = llama_model_get_vocab(model);

    // **コンテキスト作成**
    llama_context_params cparams = llama_context_default_params();
    cparams.n_ctx   = n_ctx;
    cparams.n_batch = n_batch;
    cparams.n_ubatch = n_ubatch;

    llama_context *ctx = llama_init_from_model(model, cparams);
    if (!ctx) {
        std::cerr << "ERROR: failed to init context\n";
        llama_model_free(model);
        return 1;
    }

    // プロンプトをトークン化
    int32_t tcount = llama_tokenize(vocab, prompt.c_str(), prompt.size(),
                                    nullptr, 0, false, true);
    if (tcount < 0) tcount = -tcount;
    std::vector<llama_token> prompt_tokens(tcount);
    llama_tokenize(vocab, prompt.c_str(), prompt.size(),
                   prompt_tokens.data(), prompt_tokens.size(),
                   false, true);

    // **プロンプトを評価**
    llama_batch batch = llama_batch_get_one(prompt_tokens.data(), prompt_tokens.size());
    if (llama_decode(ctx, batch) != 0) {
        std::cerr << "ERROR: prompt eval failed\n";
        llama_free(ctx);
        llama_model_free(model);
        return 1;
    }

    std::string result;
    int n_generated = 0;

    while (n_generated < n_predict) {
        const float *logits = llama_get_logits(ctx);
        int32_t n_vocab = llama_vocab_n_tokens(vocab);

        // greedy
        int best = 0;
        float best_log = logits[0];
        for (int i = 1; i < n_vocab; ++i) {
            if (logits[i] > best_log) {
                best_log = logits[i];
                best = i;
            }
        }

        // EOS判定
        if (llama_vocab_is_eog(vocab, best))
            break;

        // トークン → 文字列
        char buf[256];
        int32_t cc = llama_token_to_piece(vocab, best, buf, sizeof(buf), 0, true);
        if (cc > 0) result.append(buf, cc);

        // 次のステップ：1トークンだけ評価
        batch = llama_batch_get_one(&best, 1);
        if (llama_decode(ctx, batch) != 0)
            break;

        ++n_generated;
    }

    // **まとめてドン！出力**
    std::cout << result << std::endl;

    llama_free(ctx);
    llama_model_free(model);
    llama_backend_free();
    return 0;
}

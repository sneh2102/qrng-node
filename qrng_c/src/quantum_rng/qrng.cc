#include <napi.h>
#include "quantum_rng.h"

namespace qrng_wrapper {

Napi::Value QRNG_Init(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    qrng_ctx *ctx;
    qrng_error err = qrng_init(&ctx, nullptr, 0);

    if (err != QRNG_SUCCESS) {
        Napi::TypeError::New(env, "Failed to initialize QRNG").ThrowAsJavaScriptException();
        return env.Null();
    }

    return Napi::External<qrng_ctx>::New(env, ctx);
}

Napi::Value QRNG_GenerateBytes(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsExternal() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Expected (ctx, length)").ThrowAsJavaScriptException();
        return env.Null();
    }

    qrng_ctx* ctx = info[0].As<Napi::External<qrng_ctx>>().Data();
    size_t length = info[1].As<Napi::Number>().Uint32Value();

    Napi::Buffer<uint8_t> buffer = Napi::Buffer<uint8_t>::New(env, length);
    qrng_error err = qrng_bytes(ctx, buffer.Data(), length);

    if (err != QRNG_SUCCESS) {
        Napi::TypeError::New(env, "Failed to generate QRNG bytes").ThrowAsJavaScriptException();
        return env.Null();
    }

    return buffer;
}

Napi::Value QRNG_GenerateUint64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsExternal()) {
        Napi::TypeError::New(env, "Expected (ctx)").ThrowAsJavaScriptException();
        return env.Null();
    }

    qrng_ctx* ctx = info[0].As<Napi::External<qrng_ctx>>().Data();
    uint64_t value = qrng_uint64(ctx);

    return Napi::Number::New(env, static_cast<double>(value));
}

Napi::Value QRNG_GenerateDouble(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsExternal()) {
        Napi::TypeError::New(env, "Expected (ctx)").ThrowAsJavaScriptException();
        return env.Null();
    }

    qrng_ctx* ctx = info[0].As<Napi::External<qrng_ctx>>().Data();
    double value = qrng_double(ctx);

    return Napi::Number::New(env, value);
}

Napi::Value QRNG_GenerateRange32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 3 || !info[0].IsExternal() || !info[1].IsNumber() || !info[2].IsNumber()) {
        Napi::TypeError::New(env, "Expected (ctx, min, max)").ThrowAsJavaScriptException();
        return env.Null();
    }

    qrng_ctx* ctx = info[0].As<Napi::External<qrng_ctx>>().Data();
    int32_t min = info[1].As<Napi::Number>().Int32Value();
    int32_t max = info[2].As<Napi::Number>().Int32Value();

    int32_t result = qrng_range32(ctx, min, max);
    return Napi::Number::New(env, result);
}

Napi::Value QRNG_GenerateRange64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 3 || !info[0].IsExternal() || !info[1].IsNumber() || !info[2].IsNumber()) {
        Napi::TypeError::New(env, "Expected (ctx, min, max)").ThrowAsJavaScriptException();
        return env.Null();
    }

    qrng_ctx* ctx = info[0].As<Napi::External<qrng_ctx>>().Data();
    uint64_t min = info[1].As<Napi::Number>().Uint32Value();
    uint64_t max = info[2].As<Napi::Number>().Uint32Value();

    uint64_t result = qrng_range64(ctx, min, max);
    return Napi::Number::New(env, static_cast<double>(result));
}

Napi::Value QRNG_GetEntropyEstimate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsExternal()) {
        Napi::TypeError::New(env, "Expected (ctx)").ThrowAsJavaScriptException();
        return env.Null();
    }

    qrng_ctx* ctx = info[0].As<Napi::External<qrng_ctx>>().Data();
    double entropy = qrng_get_entropy_estimate(ctx);

    return Napi::Number::New(env, entropy);
}

Napi::Value QRNG_EntangleStates(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 3 || !info[0].IsExternal() || !info[1].IsBuffer() || !info[2].IsBuffer()) {
        Napi::TypeError::New(env, "Expected (ctx, state1, state2)").ThrowAsJavaScriptException();
        return env.Null();
    }

    qrng_ctx* ctx = info[0].As<Napi::External<qrng_ctx>>().Data();
    uint8_t* state1 = info[1].As<Napi::Buffer<uint8_t>>().Data();
    uint8_t* state2 = info[2].As<Napi::Buffer<uint8_t>>().Data();
    size_t len = info[1].As<Napi::Buffer<uint8_t>>().Length();

    qrng_entangle_states(ctx, state1, state2, len);

    return env.Null();
}

Napi::Value QRNG_MeasureState(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsExternal() || !info[1].IsBuffer()) {
        Napi::TypeError::New(env, "Expected (ctx, state)").ThrowAsJavaScriptException();
        return env.Null();
    }

    qrng_ctx* ctx = info[0].As<Napi::External<qrng_ctx>>().Data();
    uint8_t* state = info[1].As<Napi::Buffer<uint8_t>>().Data();
    size_t len = info[1].As<Napi::Buffer<uint8_t>>().Length();

    qrng_measure_state(ctx, state, len);

    return env.Null();
}

Napi::Value QRNG_ErrorString(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Expected (errorCode)").ThrowAsJavaScriptException();
        return env.Null();
    }

    int errorCode = info[0].As<Napi::Number>().Int32Value();
    return Napi::String::New(env, qrng_error_string(static_cast<qrng_error>(errorCode)));
}
Napi::Object Initialize(Napi::Env env, Napi::Object exports) {
    exports.Set("init", Napi::Function::New(env, QRNG_Init));
    exports.Set("generateBytes", Napi::Function::New(env, QRNG_GenerateBytes));
    exports.Set("generateUint64", Napi::Function::New(env, QRNG_GenerateUint64));
    exports.Set("generateDouble", Napi::Function::New(env, QRNG_GenerateDouble));
    exports.Set("generateRange32", Napi::Function::New(env, QRNG_GenerateRange32));
    exports.Set("generateRange64", Napi::Function::New(env, QRNG_GenerateRange64));
    exports.Set("getEntropyEstimate", Napi::Function::New(env, QRNG_GetEntropyEstimate));
    exports.Set("entangleStates", Napi::Function::New(env, QRNG_EntangleStates));
    exports.Set("measureState", Napi::Function::New(env, QRNG_MeasureState));
    exports.Set("errorString", Napi::Function::New(env, QRNG_ErrorString));

    return exports;  // ✅ Fix: Return `exports` instead of `void`
}


NODE_API_MODULE(qrng, Initialize)

}  // namespace qrng_wrapper

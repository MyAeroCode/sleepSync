#include <napi.h>
#include <Windows.h>

void sleepSync(const Napi::CallbackInfo& info){
    auto ms = info[0].ToNumber().Uint32Value();
    Sleep(ms);
}

Napi::Object init(Napi::Env env, Napi::Object exports){
    exports.Set("sleepSync", Napi::Function::New(env, sleepSync));
    return exports;
}

NODE_API_MODULE(sleepSync, init);

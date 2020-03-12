#include <napi.h>
#include <unistd.h>

void sleepSync(const Napi::CallbackInfo& info){
    auto ms = info[0].ToNumber().Uint32Value();
    auto us = ms * 1e3;
    usleep(us);
}

Napi::Object init(Napi::Env env, Napi::Object exports){
    exports.Set("sleepSync", Napi::Function::New(env, sleepSync));
    return exports;
}

NODE_API_MODULE(sleepSync, init);

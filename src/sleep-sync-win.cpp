#include <napi.h>
#include <Windows.h>
#include <WinBase.h>
#include <conio.h>

namespace Wait {
    LARGE_INTEGER freq;
    const uint64_t US = 1'000'000;
    const uint64_t MS = 1'000;
    const size_t BUF_SIZE = 512;

    /** Window ver, get elapsed count. */
    inline uint64_t window_get_elapsed(const LARGE_INTEGER& beg, const uint64_t rate){
        LARGE_INTEGER end;
        QueryPerformanceCounter(&end);
        return (end.QuadPart - beg.QuadPart) / (freq.QuadPart / rate );
    }

    /** Window ver, wait impl. */
    inline void window_wait(uint64_t val, int64_t rate){
        LARGE_INTEGER beg;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&beg);
        while(true){
            auto elapsed = window_get_elapsed(beg, rate);
            if(val <= elapsed) break;
        }
    }

    /** clear buffer. */
    inline void window_clear_input(char16_t *buf, size_t &idx, const size_t &size){
        for(size_t i=0; i<idx; i++){
            buf[i] = 0;
        }
        idx = 0;
    }

    /** non-block read, Return true if enter is pressed. */
    inline bool window_read_input(char16_t *buf, size_t &idx, const size_t &size){
        if(_kbhit()){
            auto c = _getwche();
            if(c == 8){
                // backspace.
                if(idx != 0) {
                    buf[--idx] = 0;
                }
            }
            else if(c == 13){
                // enter.
                putchar('\n');
                return true;
            }
            else {
                // other.
                buf[idx++] = c;
                if(idx == size) window_clear_input(buf, idx, size);
            }
        }
        return false;
    }

    /** Suspends the execution until the time-out interval elapses. */
    void uwait(const Napi::CallbackInfo &info){
        auto us = info[0].ToNumber().Int64Value();
        window_wait(us, US);
    }

    /** Suspends the execution until the time-out interval elapses. */
    void wait(const Napi::CallbackInfo& info){
        auto ms = info[0].ToNumber().Int64Value();
        window_wait(ms, MS);
    }

    /** Suspends the execution until the desired key is pressed. */
    Napi::Boolean waitKey(const Napi::CallbackInfo& info){
        //
        // check expect.
        auto napi_expect = info[0];
        int64_t expectKeyCode = -1;
        if(!napi_expect.IsUndefined()) {
            expectKeyCode = napi_expect.ToNumber().Int64Value();
        }

        //
        // check timelimit.
        auto napi_timelimit = info[1];
        int64_t timelimit = -1;
        if(!napi_timelimit.IsUndefined()) {
            timelimit = napi_timelimit.ToNumber().Int64Value();
        }

        bool response = false;
        LARGE_INTEGER beg;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&beg);
        while(true){
            if(_kbhit()){
                auto c = _getch();
                if(expectKeyCode < 0 || c == expectKeyCode) {
                    response = true;
                    break;
                }
            }
            if( 0 <= timelimit && (uint64_t)timelimit <= window_get_elapsed(beg, MS) ){
                break;
            }
        }
        return Napi::Boolean::New(info.Env(), response);
    }

    /** Suspends the execution until the desired line is typed. */
    Napi::Boolean waitLine(const Napi::CallbackInfo& info){
        std::u16string expect = info[0].ToString().Utf16Value();
        
        //
        // check timelimit.
        auto napi_timelimit = info[1];
        int64_t timelimit = -1;
        if(!napi_timelimit.IsUndefined()) {
            timelimit = napi_timelimit.ToNumber().Int64Value();
        }

        bool response = false;
        char16_t buf[BUF_SIZE]{ 0 };
        size_t idx = 0;
        LARGE_INTEGER beg;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&beg);
        while(true){
            if(window_read_input(buf, idx, BUF_SIZE)){
                if(std::u16string(buf) == expect) {
                    response = true;
                    break;
                }
                else window_clear_input(buf, idx, BUF_SIZE);
            }
            if( 0 <= timelimit && (uint64_t)timelimit <= window_get_elapsed(beg, MS) ){
                break;
            }
        }
        return Napi::Boolean::New(info.Env(), response);
    }

    /** Suspends the execution until the enter is pressed. */
    Napi::Boolean waitEnter(const Napi::CallbackInfo& info){
        //
        // check timelimit.
        auto napi_timelimit = info[0];
        int64_t timelimit = -1;
        if(!napi_timelimit.IsUndefined()) {
            timelimit = napi_timelimit.ToNumber().Int64Value();
        }

        bool response = false;
        LARGE_INTEGER beg;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&beg);
        while(true){
            if(_kbhit()){
                auto c = _getch();
                if(c == 13) {
                    response = true;
                    break;
                }
            }
            if( 0 <= timelimit && (uint64_t)timelimit <= window_get_elapsed(beg, MS) ){
                break;
            }
        }
        return Napi::Boolean::New(info.Env(), response);
    }

    /** Suspends the execution until the user confirms. */
    Napi::Boolean waitConfirm(const Napi::CallbackInfo &info){
        std::u16string ystr = info[0].ToString().Utf16Value();

        //
        // check nstr.
        auto napi_nstr = info[1];
        auto nstr_undefined = info[1].IsUndefined();
        std::u16string nstr;
        if(!nstr_undefined){
            nstr = info[1].ToString().Utf16Value();
        }

        //
        // check timelimit.
        auto napi_timelimit = info[2];
        int64_t timelimit = -1;
        if(!napi_timelimit.IsUndefined()) {
            timelimit = napi_timelimit.ToNumber().Int64Value();
        }

        bool response = false;
        char16_t buf[BUF_SIZE]{ 0 };
        size_t idx = 0;
        LARGE_INTEGER beg;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&beg);
        while(true){
            if(window_read_input(buf, idx, BUF_SIZE)){
                if(std::u16string(buf) == ystr){
                    response = true;
                    break;
                }
                else if(nstr_undefined || (!nstr_undefined && std::u16string(buf) == nstr)){
                    break;
                }
                window_clear_input(buf, idx, BUF_SIZE);
            }
            if( 0 <= timelimit && (uint64_t)timelimit <= window_get_elapsed(beg, MS) ){
                break;
            }
        }
        return Napi::Boolean::New(info.Env(), response);
    }
}



Napi::Object init(Napi::Env env, Napi::Object exports){
    exports.Set("uwait", Napi::Function::New(env, Wait::uwait));
    exports.Set("wait", Napi::Function::New(env, Wait::wait));
    exports.Set("waitKey", Napi::Function::New(env, Wait::waitKey));
    exports.Set("waitLine", Napi::Function::New(env, Wait::waitLine));
    exports.Set("waitEnter", Napi::Function::New(env, Wait::waitEnter));
    exports.Set("waitConfirm", Napi::Function::New(env, Wait::waitConfirm));
    return exports;
}

NODE_API_MODULE(sleepSync, init);

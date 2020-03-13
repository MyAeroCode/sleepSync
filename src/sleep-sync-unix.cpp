#include <napi.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/time.h>

namespace Wait {
    struct termios oldSettings;
    struct termios newSettings;
    
    /** Save the current console options. */
    void console_setting_backup(){
        tcgetattr(fileno(stdin), &oldSettings);
        newSettings = oldSettings;
    }

    /** Revert to the original console options. */
    void console_setting_restore(){
        tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
    }

    /** The non-normal mode is applied. */
    void console_setting_immediate(){
        newSettings.c_lflag &= (~ICANON);
        newSettings.c_lflag &= (~ECHO);
    }

    /** Apply the changed console options. */
    void console_setting_apply(){
        tcsetattr( fileno( stdin ), TCSANOW, &newSettings );
    }

    /** Set the keyboard input timeout. */
    int console_get_state(const int64_t& ms){
        int state;
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

        //
        // apply timelimit.
        if(0 < ms) {
            struct timeval tv;
            tv.tv_sec = ms / 1000;
            tv.tv_usec = (ms % 1000) * 1000;
            state = select(fileno(stdin)+1, &set, NULL, NULL, &tv);
        }
        else {
            state = select(fileno(stdin)+1, &set, NULL, NULL, NULL);
        }

        //
        // check error.
        if(state == 0){
            //
            // timeout.
        }
        if(state < 0){
            //
            // select error.
            perror("select error");
        }

        //
        // retrun state.
        return state;
    } 

    /** Suspends the execution until the time-out interval elapses. */
    void uwait(const Napi::CallbackInfo &info){
        auto us = info[0].ToNumber().Int64Value();
        if(0 < us){
            usleep(us);
        }
    }

    /** Suspends the execution until the time-out interval elapses. */
    void wait(const Napi::CallbackInfo& info){
        auto ms = info[0].ToNumber().Int64Value();
        if(0 < ms){
            auto us = ms * 1e3;
            usleep(us);
        }
    }

    /** Suspends the execution until the desired key is pressed. */
    Napi::Boolean waitKey(const Napi::CallbackInfo &info){
        //
        // init console setting.
        console_setting_backup();
        console_setting_immediate();
        console_setting_apply();

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
        while(true){
            if(0 < console_get_state(timelimit)) {
                char c = getchar();
                if(expectKeyCode < 0 || c == expectKeyCode) {
                    response = true;
                    break;
                }
            }
            else break;
        }

        //
        // restore console setting.
        console_setting_restore();
        return Napi::Boolean::New(info.Env(), response);
    }

    /** Suspends the execution until the desired line is typed. */
    Napi::Boolean waitLine(const Napi::CallbackInfo &info){
        std::string expect = info[0].ToString().Utf8Value();

        //
        // check timelimit.
        auto napi_timelimit = info[1];
        int64_t timelimit = -1;
        if(!napi_timelimit.IsUndefined()) {
            timelimit = napi_timelimit.ToNumber().Int64Value();
        }

        bool response = false;
        while (true)
        {
            if(0 < console_get_state(timelimit)) {
                std::string input;
                std::getline(std::cin, input);
                if(input == expect) {
                    response = true;
                    break;
                }
            }
            else break;
        }
        return Napi::Boolean::New(info.Env(), response);
    }

    /** Suspends the execution until the enter is pressed. */
    Napi::Boolean waitEnter(const Napi::CallbackInfo &info){
        //
        // init console setting.
        console_setting_backup();
        console_setting_immediate();
        console_setting_apply();

        //
        // check timelimit.
        auto napi_timelimit = info[0];
        int64_t timelimit = -1;
        if(!napi_timelimit.IsUndefined()) {
            timelimit = napi_timelimit.ToNumber().Int64Value();
        }

        bool response = false;
        while(true){
            if(0 < console_get_state(timelimit)) {
                char c = getchar();
                if(c == 10) {
                    response = true;
                    break;
                }
            }
            else break;
        }

        //
        // restore console setting.
        console_setting_restore();
        return Napi::Boolean::New(info.Env(), response);
    }

    /** Suspends the execution until the user confirms. */
    Napi::Boolean waitConfirm(const Napi::CallbackInfo &info){
        std::string ystr = info[0].ToString().Utf8Value();

        //
        // check nstr.
        auto napi_nstr = info[1];
        auto nstr_undefined = info[1].IsUndefined();
        std::string nstr;
        if(!nstr_undefined){
            nstr = info[1].ToString().Utf8Value();
        }

        //
        // check timelimit.
        auto napi_timelimit = info[2];
        int64_t timelimit = -1;
        if(!napi_timelimit.IsUndefined()) {
            timelimit = napi_timelimit.ToNumber().Int64Value();
        }

        bool response = false;
        while(true){
            if(0 < console_get_state(timelimit)) {
                std::string inputed;
                std::getline(std::cin, inputed);
                if(inputed == ystr) {
                    response = true;
                    break;
                }
                if( nstr_undefined || (!nstr_undefined && inputed == nstr)) {
                    break;
                }
            }
            else break;
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

NODE_API_MODULE(wait, init);

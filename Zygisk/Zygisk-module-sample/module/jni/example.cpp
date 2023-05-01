#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zygisk.hpp"
#include "experimental/string"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "MyModule", __VA_ARGS__)

using zygisk::Api;
using zygisk::AppSpecializeArgs;
using zygisk::ServerSpecializeArgs;

static jstring my_method(JNIEnv* env, jclass clazz, jlong windowPtr,
                         jint row, jint column) {
    return nullptr;
};

class ExampleModule : public zygisk::ModuleBase {
public:
    void onLoad(zygisk::Api *api, JNIEnv *env) override {
        this->api = api;
        this->env = env;
    }
    void preAppSpecialize(zygisk::AppSpecializeArgs *args) override {
        const char *nice_name = env->GetStringUTFChars(args->nice_name, nullptr);
        const char *nice_name2 = "com.example.mycheckapp";

        if (strcmp(nice_name, nice_name2) == 0) {
            JNINativeMethod methods[] = { {"nativeGetString", "(JII)Ljava/lang/String;", (void*)(my_method)} };

            api->hookJniNativeMethods(env, "android/database/CursorWindow", methods, 1);
        }
    }
private:
    zygisk::Api *api;
    JNIEnv *env;
    int counter = 0;


    void preSpecialize(const char *process, const char *name, const char *dir) {
        // Demonstrate connecting to to companion process
        // We ask the companion for a random number
        unsigned r = 0;
        int fd = api->connectCompanion();
        read(fd, &r, sizeof(r));
        close(fd);

        LOGD("process=[%s], r=[%u], app_data_dir =[%s], nice-name =[%s]\n", process, r, dir, name);

        // Since we do not hook any functions, we should let Zygisk dlclose ourselves
        //api->setOption(zygisk::Option::DLCLOSE_MODULE_LIBRARY);
    }
};

REGISTER_ZYGISK_MODULE(ExampleModule)

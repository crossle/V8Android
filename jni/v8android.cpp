/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "v8android.h"
#include <string.h>

v8::Persistent<v8::Context> PrimaryContext;

extern "C" void Java_me_crossle_v8android_MainActivity_nativeInit(JNIEnv * env, jobject obj) {
    // log what's happening
    __android_log_write(ANDROID_LOG_DEBUG, "V8 in NDK", "INITIALIZING V8");
    // can be placed at any scope resolution level, this will be redeclared in any V8 aware function

    using namespace v8;

    // create the scope and context
    // governs local handles
    HandleScope localscope;
    // object template used to create the global object of our context
    Local<ObjectTemplate> global = ObjectTemplate::New();
    // declaration and instantiation of the primary context
    PrimaryContext = Context::New(NULL, global);
}

/**
 *
 */
extern "C" jstring Java_me_crossle_v8android_MainActivity_runScript(JNIEnv * env, jobject obj, jstring name, jstring message) {
    using namespace v8;
    HandleScope scope;
    TryCatch tc;
    Context::Scope context_scope(PrimaryContext);
    jstring retval;
    jboolean isCopy;

    Handle<String> nme = String::New(env->GetStringChars(name, &isCopy));
    Handle<String> cmd = String::New(env->GetStringChars(message, &isCopy));

    Handle<Script> script = Script::Compile(cmd, nme);

    if (script.IsEmpty()) {
        return env->NewStringUTF("Error: script is empty!");
    }

    __android_log_write(ANDROID_LOG_DEBUG, "V8Android", "Hello world V8");

    Local<Value> result = script->Run();

    if (result.IsEmpty()) {
        __android_log_write(ANDROID_LOG_DEBUG, "V8Android", "RESULT IS EMPTY");
        String::Utf8Value error(tc.Exception());
        __android_log_write(ANDROID_LOG_DEBUG, "V8Android", *error);
    }
    String::Utf8Value retstr(result);
    retval = env->NewStringUTF(*retstr);
    return retval;
}


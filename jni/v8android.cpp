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

using namespace v8;

// callback function
static Handle<Value> readUrl(const Arguments & args);

extern "C" jstring Java_me_crossle_v8android_MainActivity_runScript(JNIEnv *env, jobject obj, jstring code, jstring function, jstring url) {

    // Get the default Isolate created at startup.
    Isolate* isolate = Isolate::GetCurrent();

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    Handle<ObjectTemplate> global_templ = ObjectTemplate::New() ;
    global_templ->Set(String::New("readUrl"),
                      FunctionTemplate::New(readUrl)) ;

    Persistent<Context> exec_context = Context::New(NULL, global_templ);
    Context::Scope context_scope(exec_context);

    Handle<String> js_source = String::New(env->GetStringChars(code, NULL));
    Handle<String> js_function_name = String::New(env->GetStringChars(function, NULL));
    Handle<Value> js_param = String::New(env->GetStringChars(url, NULL));

    Handle<Script> js_compiled = Script::Compile(js_source);

    if (js_compiled.IsEmpty()) {
        return env->NewStringUTF("Error: script is empty!");
    }
    __android_log_write(ANDROID_LOG_DEBUG, "V8Android", "Hello world V8");

    js_compiled->Run();

    Handle<Value> js_result;
    Handle<Value> js_function_val = exec_context->Global()->Get(js_function_name);
    if (js_function_val->IsFunction()) {
      Handle<Function> js_func = Handle<Function>::Cast(js_function_val);
      int len = 1;
      Handle<Value> argm[len];
      argm[0] = js_param;
      js_result = js_func->Call(exec_context->Global(), len, argm);
    }

    // Dispose the persistent context.
    exec_context.Dispose(isolate);

    String::Utf8Value retstr(js_result);
    jstring retval = env->NewStringUTF(*retstr);
    return retval;
}

static Handle<Value> readUrl(const Arguments & args) {
  if (args.Length() == 1)
    return args[0]->ToString();
  return Undefined();
}

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

#ifndef _V8ANDROID_H
#define _V8ANDROID_H

#include <jni.h>
#include <v8.h>
#include <android/log.h>

/**
 * initialize the V8 execution environment for v8 scripts
 */
extern "C" void Java_me_crossle_v8android_MainActivity_nativeInit(JNIEnv * env, jobject obj);
/**
 * execute a script from native
 */
extern "C" jstring Java_me_crossle_v8android_MainActivity_runScript(JNIEnv * env, jobject obj, jstring name, jstring message);

#endif // _V8ANDROID_H

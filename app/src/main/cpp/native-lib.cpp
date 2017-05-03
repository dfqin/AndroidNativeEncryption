//
// Created by dfqin on 2017/3/2.
//

#include <jni.h>
#include <string>
#include "Utils.h"
#include "EnvChecker.h"
#include "JavaClassesDef.h"
#include "EncodeUtils.h"
#include <sys/ptrace.h>


static jbyteArray encrypt(JNIEnv *env, jclass instance, jobject contextObject, jbyteArray data) {

    if (EnvChecker::isValid(env, contextObject)) {
        return EncodeUtils::encryptData(env, data, 1);
    } else {
        showToast(env, env->NewStringUTF("encryptData非法调用"));
        return data;
    }
}

static jbyteArray decrypt(JNIEnv *env, jclass instance, jobject contextObject, jbyteArray data) {

    if (EnvChecker::isValid(env, contextObject)) {
        return EncodeUtils::decryptData(env, data, 1);
    } else {
        showToast(env, env->NewStringUTF("decryptData非法调用"));
        return data;
    }
}

static jstring geneSign(JNIEnv *env, jclass instance, jobject contextObject, jstring str) {

    if (EnvChecker::isValid(env, contextObject)) {
        const char *data = env->GetStringUTFChars(str, 0);
        jstring temp = EncodeUtils::geneSign(env, str);
        env->ReleaseStringUTFChars(str, data);
        return temp;
    } else {
        showToast(env, env->NewStringUTF("getSign非法调用"));
        return str;
    }
}

static JNINativeMethod nMethods[] = {
        { SecureUtil_encryptData_Method, SecureUtil_encryptData_Param, (void*)encrypt },
        { SecureUtil_decryptData_Method, SecureUtil_decryptData_Param, (void*)decrypt },
        { SecureUtil_getSign_Method, SecureUtil_getSign_Param, (void*)geneSign}
};

JNIEXPORT jint JNICALL JNI_OnLoad (JavaVM* vm,void* reserved){

    //防止动态调试
    ptrace(PTRACE_TRACEME, 0, 0, 0);

    JNIEnv* env = NULL;
    jint result=-1;
    if(vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
        return result;

    baseClasses.contextClass = (jclass)env->NewGlobalRef(env->FindClass("android/content/Context"));
    baseClasses.signatureClass = (jclass)env->NewGlobalRef(env->FindClass("android/content/pm/Signature"));
    baseClasses.packageManagerClass = (jclass)env->NewGlobalRef(env->FindClass("android/content/pm/PackageManager"));
    baseClasses.packageInfoClass = (jclass)env->NewGlobalRef(env->FindClass("android/content/pm/PackageInfo"));
    baseClasses.jniUtilClass = (jclass)env->NewGlobalRef(env->FindClass(SecureUtil_Clz));

    initAppEnv(env);

    env->RegisterNatives(baseClasses.jniUtilClass, nMethods, sizeof(nMethods) / sizeof(nMethods[0]));

    gIsValid = false;

    logV("JNI OnLoad");

    return JNI_VERSION_1_4;
}
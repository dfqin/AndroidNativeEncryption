//
// Created by dfqin on 2017/3/16.
//

#include "Utils.h"
#include "JavaClassesDef.h"

AppEnv appEnv;
BaseClasses baseClasses;
bool gIsValid;
bool isDebug;
void initDebug(JNIEnv *env);

/**
 * 初始化一些App配置信息
 */
void initAppEnv(JNIEnv *env) {

    jmethodID methodGetDeviceID = env->GetStaticMethodID(baseClasses.jniUtilClass, SecureUtil_getDeviceId_Method, SecureUtil_getDeviceId_Param);
    jstring deviceId = (jstring)env->CallStaticObjectMethod(baseClasses.jniUtilClass, methodGetDeviceID);
    string strDeviceId = jstring2String(env, deviceId);

    jmethodID methodGetAppVersion = env->GetStaticMethodID(baseClasses.jniUtilClass, SecureUtil_getAppVersion_Method, SecureUtil_getAppVersion_Param);
    jstring appVersion = (jstring)env->CallStaticObjectMethod(baseClasses.jniUtilClass, methodGetAppVersion);
    string strAppVersion = jstring2String(env, appVersion);

    jmethodID methodGetChannel = env->GetStaticMethodID(baseClasses.jniUtilClass, SecureUtil_getChannel_Method, SecureUtil_getChannel_Param);
    jstring channel = (jstring)env->CallStaticObjectMethod(baseClasses.jniUtilClass, methodGetChannel);
    string strChannel = jstring2String(env, channel);

    initDebug(env);

    appEnv.deviceID = strDeviceId;
    appEnv.appVersion = strAppVersion;
    appEnv.appChannel = strChannel;

}

void initDebug(JNIEnv *env) {
    char name[30] = PACKAGE_FRONT;
    const char* last = PACKAGE_END;
    const char* clazzName = ".BuildConfig";
    strcat(name, last); //拼接
    strcat(name, clazzName);
    for (int i = 0; i < 30; i++) {
        if (name[i] == '\0') {
            break;
        }
        if (name[i] == '.') {
            name[i] = '/';
        }
    }
    jclass clazz = env->FindClass(name);
    jfieldID fieldId = env->GetStaticFieldID(clazz, "DEBUG", "Z");
    isDebug = env->GetStaticBooleanField(clazz, fieldId);
}

string jstring2String(JNIEnv* env, jstring str) {
    if (str == NULL){
        return "";
    }
    const char *c_str1 = NULL;
    c_str1 = env->GetStringUTFChars(str, NULL);
    string result(c_str1);
    env->ReleaseStringUTFChars(str, c_str1);
    return result;
}

void showToast(JNIEnv* env, jstring str) {
    jmethodID methodShowToast = env->GetStaticMethodID(baseClasses.jniUtilClass, SecureUtil_showToast_Method, SecureUtil_showToast_Param);
    env->CallStaticVoidMethod(baseClasses.jniUtilClass, methodShowToast, str);
}

void logV(const char* log) {
    if (isDebug) {
        __android_log_print(ANDROID_LOG_VERBOSE, "Tag_Native", "%s", log);
    }
}

void logD(char* log) {
    if (isDebug) {
        __android_log_print(ANDROID_LOG_DEBUG, "Tag_Native", "%s", log);
    }
}

void logI(char* log) {
    if (isDebug) {
        __android_log_print(ANDROID_LOG_INFO, "Tag_Native", "%s", log);
    }
}

void logW(char* log) {
    if (isDebug) {
        __android_log_print(ANDROID_LOG_WARN, "Tag_Native", "%s", log);
    }
}

void logE(char* log) {
    if (isDebug) {
        __android_log_print(ANDROID_LOG_ERROR, "Tag_Native", "%s", log);
    }
}


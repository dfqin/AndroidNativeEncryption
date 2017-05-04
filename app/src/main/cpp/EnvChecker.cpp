//
// Created by dfqin on 2017/3/7.
//

#include "EnvChecker.h"
#include <string>

using namespace std;

bool EnvChecker::isValid(JNIEnv* env, jobject context) {

    if (!gIsValid) {
        gIsValid = (checkSign(env, context, baseClasses) && checkPkgName(env, context, baseClasses));
    }
    return gIsValid;
}

//获取签名信息
jstring EnvChecker::getSign(JNIEnv* env, jobject context, BaseClasses classes) {
    jmethodID getPackageManagerId = env->GetMethodID(classes.contextClass, "getPackageManager","()Landroid/content/pm/PackageManager;");
    jmethodID signToStringId = env->GetMethodID(classes.signatureClass, "toCharsString","()Ljava/lang/String;");
    jmethodID getPackageInfoId = env->GetMethodID(classes.packageManagerClass, "getPackageInfo","(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageManagerObject =  env->CallObjectMethod(context, getPackageManagerId);

    jstring pkgName = getPackageName(env, context, classes);

    jobject packageInfoObject = env->CallObjectMethod(packageManagerObject, getPackageInfoId,pkgName, 64);
    jfieldID signaturefieldID =env->GetFieldID(classes.packageInfoClass,"signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signatureArray = (jobjectArray)env->GetObjectField(packageInfoObject, signaturefieldID);
    jobject signatureObject =  env->GetObjectArrayElement(signatureArray,0);
    jstring sign = (jstring)env->CallObjectMethod(signatureObject, signToStringId);
    return sign;
}

//检查签名(截取了 [8, 15] [len-24, len-8] 两段比较)
bool EnvChecker::checkSign(JNIEnv* env, jobject context, BaseClasses classes) {

    jstring signString = getSign(env, context, classes);
    const char* pSign = env->GetStringUTFChars(signString, 0);

    int len = strlen(pSign);
    char start[17] = "";
    char last[17] = "";

    strncpy(start, pSign + 8, 16);
    strncpy(last, pSign + len - 24, 16);

    char encryptSign[33] = "";
    strcat(encryptSign, start);
    strcat(encryptSign, last);

    char sign[33] = "";
    if (isDebug) {
        strcat(sign, SIGN_FRONT_DEBUG);
        strcat(sign, SIGN_END_DEBUG);
    } else {
        strcat(sign, SIGN_FRONT_RELEASE);
        strcat(sign, SIGN_END_RELEASE);
    }

    bool isValid = strcmp(sign, encryptSign) == 0;
    env->ReleaseStringUTFChars(signString, pSign);
    return isValid;
}

//获取包名
jstring EnvChecker::getPackageName(JNIEnv* env, jobject context, BaseClasses classes) {
    jmethodID getPackageNameId = env->GetMethodID(classes.contextClass, "getPackageName","()Ljava/lang/String;");
    jstring packNameString =  (jstring)env->CallObjectMethod(context, getPackageNameId);
    return packNameString;
}

//检查包名
bool EnvChecker::checkPkgName(JNIEnv* env, jobject context, BaseClasses classes) {
    jstring  pkgName = getPackageName(env, context, classes);

    char name[20] = PACKAGE_FRONT;
    const char* last = PACKAGE_END;
    strcat(name, last); //拼接

    const char* curPkgName = env->GetStringUTFChars(pkgName, 0);
    bool isEqual = strcmp(curPkgName, name) == 0;
    env->ReleaseStringUTFChars(pkgName, curPkgName);
    return isEqual;
}

//
// Created by dfqin on 2017/3/9.
//
#include <jni.h>

#ifndef WINANDROID_ENCODEUTILS_H
#define WINANDROID_ENCODEUTILS_H

class EncodeUtils {

public:
    static jbyteArray encryptData(JNIEnv *env, jbyteArray& data, int type);
    static jbyteArray decryptData(JNIEnv *env, jbyteArray& data, int type);
    static jstring geneSign(JNIEnv *env, jstring& data);
};


#endif //WINANDROID_ENCODEUTILS_H

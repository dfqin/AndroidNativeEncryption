/**
 * Created by dfqin on 2017/3/8.
 *
 * C++中用到的Java类的定义
 * _Clz结尾表示一个class; _Method结尾表示一个成员方法; _Param结尾表示方法的参数
 *
 */

#ifndef JAVA_CLASSES_DEF_H
#define JAVA_CLASSES_DEF_H

/*******------类分割线-------**********/

#define SecureUtil_Clz  "com/dfqin/encrypt/SecureUtil"

#define SecureUtil_getDeviceId_Method  "getDeviceId"
#define SecureUtil_getDeviceId_Param  "()Ljava/lang/String;"

#define SecureUtil_getAppVersion_Method "getAppVersion"
#define SecureUtil_getAppVersion_Param "()Ljava/lang/String;"

#define SecureUtil_getChannel_Method "getChannel"
#define SecureUtil_getChannel_Param "()Ljava/lang/String;"

#define SecureUtil_showToast_Method "showToast"
#define SecureUtil_showToast_Param "(Ljava/lang/String;)V"

#define SecureUtil_encryptData_Method "encryptData"
#define SecureUtil_encryptData_Param "(Landroid/content/Context;[B)[B"

#define SecureUtil_decryptData_Method "decryptData"
#define SecureUtil_decryptData_Param "(Landroid/content/Context;[B)[B"

#define SecureUtil_getSign_Method "getSign"
#define SecureUtil_getSign_Param "(Landroid/content/Context;Ljava/lang/String;)Ljava/lang/String;"

/*******------类分割线-------**********/


#endif //JAVA_CLASSES_DEF_H
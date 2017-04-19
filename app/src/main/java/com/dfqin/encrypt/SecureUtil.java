package com.dfqin.encrypt;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by dfqin on 2017/4/7.
 */

public class SecureUtil {

    static {
        System.loadLibrary("native-lib");
    }

    public static byte[] encryptData(byte[] data) {
        return encryptData(BaseApplication.getInstance(), data);
    }

    public static byte[] decryptData(byte[] data) {
        return decryptData(BaseApplication.getInstance(), data);
    }

    public static String getSign(String data) {
        return getSign(BaseApplication.getInstance(), data);
    }

    public static String getDeviceId() {
        return "deviceId";
    }

    public static String getAppVersion() {
        return "1.0";
    }

    public static String getChannel() {
        return "huawei";
    }

    public static void showToast(String tips) {
        Toast.makeText(BaseApplication.getInstance(), tips, Toast.LENGTH_SHORT).show();
    }

    native private static byte[] encryptData(Context context, byte[] data);
    native private static byte[] decryptData(Context context, byte[] data);
    native private static String getSign(Context context, String data);
}

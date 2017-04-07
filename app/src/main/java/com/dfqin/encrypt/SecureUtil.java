package com.dfqin.encrypt;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by dfqin on 2017/4/7.
 */

public class SecureUtil {
    native public static byte[] encryptData(Context context, byte[] data);
    native public static byte[] decryptData(Context context, byte[] data);
    native public static String getSign(Context context, String data);

    static {
        System.loadLibrary("native-lib");
    }

    public static String getDeviceId() {
        return "deviceId";
    }

    public static String getAppVersion() {
        return "1.0";
    }

    public static String getChannel() {
        return "Win";
    }

    public static boolean isDebug() {
        return BuildConfig.DEBUG;
    }

    public static void showToast(String tips) {
        Toast.makeText(BaseApplication.getInstance(), tips, Toast.LENGTH_SHORT).show();
    }
}

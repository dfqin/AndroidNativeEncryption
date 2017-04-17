package com.dfqin.encrypt;

import java.security.MessageDigest;

/**
 * Created by dfqin on 2017/3/20.
 */


public class MD5Util {
    private static final char[] HEX_DIGITS = new char[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    public MD5Util() {
    }

    private static String toHexString(byte[] b) {
        StringBuilder sb = new StringBuilder(b.length * 2);

        for(int i = 0; i < b.length; ++i) {
            sb.append(HEX_DIGITS[(b[i] & 240) >>> 4]);
            sb.append(HEX_DIGITS[b[i] & 15]);
        }

        return sb.toString();
    }

    public static String to32Str(String sourceString) throws Exception {
        return toHexString(toByte(sourceString));
    }

    public static String to16Str(String sourceString) throws Exception {
        return to32Str(sourceString).substring(8, 24);
    }

    public static byte[] toByte(String sourceString) throws Exception {
        MessageDigest digest = MessageDigest.getInstance("MD5");
        digest.update(sourceString.getBytes());
        byte[] messageDigest = digest.digest();
        return messageDigest;
    }
}
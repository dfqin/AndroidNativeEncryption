package com.dfqin.encrypt;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static {
        System.loadLibrary("native-lib");
    }


    private EditText input;
    private TextView resultText;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        input = (EditText)findViewById(R.id.input_ori);
        resultText = (TextView)findViewById(R.id.text_result);

        findViewById(R.id.btn_native_encode).setOnClickListener(this);
        findViewById(R.id.btn_java_encode).setOnClickListener(this);

        findViewById(R.id.btn_native_decode).setOnClickListener(this);
        findViewById(R.id.btn_java_decode).setOnClickListener(this);

        findViewById(R.id.btn_java_sign).setOnClickListener(this);
        findViewById(R.id.btn_native_sign).setOnClickListener(this);
    }


    @Override
    public void onClick(View v) {

        String ori  = input.getText().toString().trim();
        String result = "";
        switch (v.getId()) {
            case R.id.btn_java_encode:
                result = javaEncode(ori);
                break;
            case R.id.btn_native_encode:
                result = nativeEncode(ori);
                break;
            case R.id.btn_java_decode:
                result = javaDecode(ori);
                break;
            case R.id.btn_native_decode:
                result = nativeDecode(ori);
                break;
            case R.id.btn_java_sign:
                result = javaSign(ori);
                break;
            case R.id.btn_native_sign:
                result = nativeSign(ori);
                break;
        }
        resultText.setText(result);
    }


    private String javaEncode(String str) {
        try {
            byte[] key = MD5Util.toByte(geneKey());
            SecretKeySpec skeySpec = new SecretKeySpec(key, "AES");
            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");

            byte[] iv = { 49, 50, 51, 52, 49, 50, 51, 52, 49, 50, 51, 52, 49, 50, 51, 52};
            cipher.init(Cipher.ENCRYPT_MODE, skeySpec, new IvParameterSpec(iv));
            byte[] encrypted = cipher.doFinal(str.getBytes());

            String base64 = Base64.encodeToString(encrypted, Base64.DEFAULT);
            return base64;
        } catch (Exception e) {
            e.printStackTrace();
            return str;
        }
    }

    private String javaDecode(String str) {
        try {
            byte[] deData = Base64.decode(str, Base64.DEFAULT);
            byte[] key = MD5Util.toByte(geneKey());
            SecretKeySpec skeySpec = new SecretKeySpec(key, "AES");
            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");

            byte[] iv = { 49, 50, 51, 52, 49, 50, 51, 52, 49, 50, 51, 52, 49, 50, 51, 52};
            cipher.init(Cipher.DECRYPT_MODE, skeySpec, new IvParameterSpec(iv));
            byte[] oriData = cipher.doFinal(deData);
            return new String(oriData);
        } catch (Exception e) {
            e.printStackTrace();
            return str;
        }
    }

    public String javaSign(String param) {
        String salt = geneKey();
        String key = salt + param + salt;
        String sign = null;
        try {
            sign = MD5Util.to32Str(key);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return sign;
    }

    private String nativeEncode(String str) {
        byte[] enData = SecureUtil.encryptData(this, str.getBytes());
        String result = new String(Base64.encode(enData, Base64.DEFAULT));
        return result;
    }

    private String nativeDecode(String str) {
        byte[] deData = Base64.decode(str, Base64.DEFAULT);
        byte[] oriData = SecureUtil.decryptData(this, deData);
        String oriStr = new String(oriData);
        return oriStr;
    }

    private String nativeSign(String param) {
        return SecureUtil.getSign(this, param);
    }

    private String geneKey() {
        return SecureUtil.getDeviceId() + "appKey" + SecureUtil.getDeviceId();
    }

}

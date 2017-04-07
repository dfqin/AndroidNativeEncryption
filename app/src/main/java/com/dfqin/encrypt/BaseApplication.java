package com.dfqin.encrypt;

import android.app.Application;

/**
 * Created by dfqin on 2017/4/7.
 */

public class BaseApplication extends Application {

    private static BaseApplication instance;

    public static BaseApplication getInstance() {
        return instance;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        instance = this;
    }
}

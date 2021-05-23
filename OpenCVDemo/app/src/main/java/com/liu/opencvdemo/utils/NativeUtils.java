package com.liu.opencvdemo.utils;

import android.graphics.Bitmap;

public class NativeUtils {
    static {
        System.loadLibrary("native-lib");
    }


    public static native String stringFromJNI();

    public static native Object testPio(Object src);
}

package com.liu.opencvdemo.utils;

public class NativeUtils {
    static {
        System.loadLibrary("native-lib");
    }


    public static native String stringFromJNI();
}

//
// Created by liuyz on 2019-12-11.
//

#ifndef PRACTICEFRAME_BITMAPUTILS_H
#define PRACTICEFRAME_BITMAPUTILS_H


#include <jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include "opencvhead.h"

#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "error", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "debug", __VA_ARGS__))

extern "C" {
void BitmapToMat(JNIEnv *env, jobject &bitmap, Mat &mat);

void MatToBitmap(JNIEnv *env, Mat &mat, jobject &bitmap);
}


#endif //PRACTICEFRAME_BITMAPUTILS_H

#include <jni.h>
#include <string>

#include "include/opencv2/opencv.hpp"

using namespace cv;

extern "C" JNIEXPORT jstring JNICALL
Java_com_liuyz_opencvdemo2_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    Mat mat=Mat(640,480,CV_8UC3);

    mat.release();

    std::string hello =
            getVersionString();
//            "Hello from C++ ";

    return env->NewStringUTF(
            hello.c_str()
            );
}
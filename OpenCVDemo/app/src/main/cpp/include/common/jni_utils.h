//
// Created by liuyz on 2018/10/30.
//
#include <jni.h>
#include <malloc.h>
#include <string.h>
#include <android/log.h>
#define TAG "Utils"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)

extern "C" {
char *jstringTochar(JNIEnv *env, jstring jstr);

jstring charTojstring(JNIEnv *env, const char *pat);

jobject
generateSyFace(JNIEnv *env, int width, int height, int rot, int num, int *src, unsigned char *pStr,
               int pStrLen);


bool YV12ToBGR24_Table(unsigned char *pYUV, unsigned char *pBGR24, int width, int height);

int Rotation90Right(unsigned char *src, unsigned char *des, int srcW, int srcH, int channel);

int Rotation180Right(unsigned char *src, unsigned char *des, int srcW, int srcH, int channel);

int Rotation270Right(unsigned char *src, unsigned char *des, int srcW, int srcH, int channel);

}
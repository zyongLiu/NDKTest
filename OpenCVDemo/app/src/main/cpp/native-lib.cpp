#include <jni.h>
#include <string>

#include "common/opencvhead.h"
#include "common/bitmapUtils.h"
#include "common/jni_utils.h"
#include "common/crop.h"


extern "C" JNIEXPORT jstring JNICALL
Java_com_liu_opencvdemo_utils_NativeUtils_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
JNIEXPORT jobject JNICALL Java_com_liu_opencvdemo_utils_NativeUtils_testPio
        (JNIEnv *env, jclass cls,jobject srcBitmap){
    Mat mat;
    BitmapToMat(env, srcBitmap, mat);
    Point root_points[1][4];
    root_points[0][0] = Point(10,10);
    root_points[0][1] = Point(10,200);
    root_points[0][2] = Point(200,150);
    root_points[0][3] = Point(210,20);
    const Point* ppt[1]={root_points[0]};
    int npt[]={4};
    fillPoly(mat,ppt,npt,1,Scalar(255));
    MatToBitmap(env,mat,srcBitmap);
    return srcBitmap;
}

JNIEXPORT void JNICALL Java_com_synodata_detection_DetectionNative_cropMirror
        (JNIEnv *env, jobject, jbyteArray jbrg, jint jw, jint jh, jint jleft, jint jtop, jint jrWidth, jint jrHeight, jobject jbitmap){
    jbyte *date = env->GetByteArrayElements(jbrg, NULL);
    jsize len = env->GetArrayLength(jbrg);

    unsigned char *dataChar1 = (unsigned char *) malloc(len * sizeof(unsigned char));
    memcpy(dataChar1, date, len * sizeof(unsigned char));
    env->ReleaseByteArrayElements(jbrg, date, 0);

    Mat src(jh, jw, CV_8UC3, dataChar1);
    cvtColor(src, src, COLOR_BGR2RGB);

    Mat temp(src,Rect(jleft,jtop,jrWidth,jrHeight));

    flip(temp,temp,1);

    MatToBitmap(env,temp,jbitmap);

    temp.release();
    src.release();

    free(dataChar1);
}

JNIEXPORT void JNICALL Java_com_synodata_detection_DetectionNative_tBGR2Bitmap___3BIILjava_lang_Object_2
        (JNIEnv *env, jclass, jbyteArray jbrg, jint jw, jint jh, jobject jbitmap){
    jbyte *date = env->GetByteArrayElements(jbrg, NULL);
    jsize len = env->GetArrayLength(jbrg);

    unsigned char *dataChar1 = (unsigned char *) malloc(len * sizeof(unsigned char));
    memcpy(dataChar1, date, len * sizeof(unsigned char));
    env->ReleaseByteArrayElements(jbrg, date, 0);
    Mat src(jh, jw, CV_8UC3, dataChar1);
    cvtColor(src, src, COLOR_BGR2RGB);

    MatToBitmap(env,src,jbitmap);

    src.release();

    free(dataChar1);

}

JNIEXPORT jint JNICALL Java_com_synodata_detection_DetectionNative_saveBGR
        (JNIEnv *env, jclass, jbyteArray jbgr, jint jw, jint jh, jstring jpath){
    jbyte *date = env->GetByteArrayElements(jbgr, NULL);
    jsize len = env->GetArrayLength(jbgr);

    unsigned char *dataChar1 = (unsigned char *) malloc(len * sizeof(unsigned char));
    memcpy(dataChar1, date, len * sizeof(unsigned char));
    env->ReleaseByteArrayElements(jbgr, date, 0);

    Mat src(jh, jw, CV_8UC3, dataChar1);
//    cvtColor(src, src, COLOR_BGR2BGR565);

    bool res=imwrite(jstringTochar(env,jpath), src);

    src.release();

    free(dataChar1);

    return res;
}
JNIEXPORT jint JNICALL Java_com_synodata_detection_DetectionNative_saveYUV
        (JNIEnv *env, jclass, jbyteArray jbgr, jint jw, jint jh, jstring jpath){
    jbyte *date = env->GetByteArrayElements(jbgr, NULL);
    jsize len = env->GetArrayLength(jbgr);

    unsigned char *dataChar1 = (unsigned char *) malloc(len * sizeof(unsigned char));
    memcpy(dataChar1, date, len * sizeof(unsigned char));
    env->ReleaseByteArrayElements(jbgr, date, 0);

    Mat src(jh * 3 / 2, jw, CV_8UC1, dataChar1);
    cvtColor(src, src, COLOR_YUV2BGR_NV21);

    bool res=imwrite(jstringTochar(env,jpath), src);

    src.release();

    free(dataChar1);

    return res;

}

JNIEXPORT jbyteArray JNICALL Java_com_synodata_detection_DetectionNative_tBitmap2BGR
        (JNIEnv *env, jclass, jobject jBitmap){

    Mat src ;
    BitmapToMat(env,jBitmap,src);
    cvtColor(src,src,COLOR_RGBA2BGR);
    jbyteArray byteArray = env->NewByteArray(3*src.rows*src.cols);
    env->SetByteArrayRegion(byteArray, 0, 3*src.rows*src.cols,
                            reinterpret_cast<const jbyte *>(src.data));
    return byteArray;

}

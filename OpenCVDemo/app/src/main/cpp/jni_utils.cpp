//
// Created by liuyz on 2018/10/30.
//
#include <common/jni_utils.h>
#include <malloc.h>
#include <string.h>

extern "C" {

char *jstringTochar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (env)->FindClass("java/lang/String");
    jstring strencode = (env)->NewStringUTF("GB2312");
    jmethodID mid = (env)->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (env)->CallObjectMethod(jstr, mid,
                                                           strencode); // String .getByte("GB2312");
    jsize alen = (env)->GetArrayLength(barr);
    jbyte *ba = (env)->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (env)->ReleaseByteArrayElements(barr, ba, 0); //
    (env)->DeleteLocalRef(clsstring);
    (env)->DeleteLocalRef(strencode);
    return rtn;
}

//char* to jstring
jstring charTojstring(JNIEnv *env, const char *pStr) {
    int strLen = strlen(pStr);
    jclass jstrObj = (env)->FindClass("java/lang/String");
    jmethodID methodId = (env)->GetMethodID(jstrObj, "<init>", "([BLjava/lang/String;)V");
    jbyteArray byteArray = (env)->NewByteArray(strLen);
    jstring encode = (env)->NewStringUTF("utf-8");

    (env)->SetByteArrayRegion(byteArray, 0, strLen, (jbyte *) pStr);
    jstring retStr = (jstring) (env)->NewObject(jstrObj, methodId, byteArray, encode);
    (env)->DeleteLocalRef(byteArray);
    (env)->DeleteLocalRef(encode);
    return retStr;
}

jobject
generateSyFace(JNIEnv *env, int width, int height, int rot, int num, int *src, unsigned char *pStr,
               int pStrLen) {
    LOGD("start generate SYFace");
    jclass jstrObj = (env)->FindClass("com/synodata/bean/SYFace");
    if (jstrObj == NULL)
        LOGD("not find SYFace");
    jmethodID methodId = (env)->GetMethodID(jstrObj, "<init>", "(IIII[I[B)V");
    if (methodId == NULL)
        LOGD("not find methodId");

    jbyteArray byteArray = (env)->NewByteArray(pStrLen);
    (env)->SetByteArrayRegion(byteArray, 0, pStrLen, (jbyte *) pStr);
    LOGD("start NewObject SYFace");
    jintArray intArray = env->NewIntArray(14 * num);
    env->SetIntArrayRegion(intArray, 0, 14 * num, src);

    jobject retStr = (env)->NewObject(jstrObj, methodId, width, height, rot, num, intArray,
                                      byteArray);
    env->DeleteLocalRef(intArray);
    (env)->DeleteLocalRef(byteArray);
    return retStr;
}

static int Table_fv1[256] = {-180, -179, -177, -176, -174, -173, -172, -170, -169, -167, -166, -165,
                             -163, -162, -160, -159, -158, -156, -155, -153, -152, -151, -149, -148,
                             -146, -145, -144, -142, -141, -139, -138, -137, -135, -134, -132, -131,
                             -130, -128, -127, -125, -124, -123, -121, -120, -118, -117, -115, -114,
                             -113, -111, -110, -108, -107, -106, -104, -103, -101, -100, -99, -97,
                             -96, -94, -93, -92, -90, -89, -87, -86, -85, -83, -82, -80, -79, -78,
                             -76, -75, -73, -72, -71, -69, -68, -66, -65, -64, -62, -61, -59, -58,
                             -57, -55, -54, -52, -51, -50, -48, -47, -45, -44, -43, -41, -40, -38,
                             -37, -36, -34, -33, -31, -30, -29, -27, -26, -24, -23, -22, -20, -19,
                             -17, -16, -15, -13, -12, -10, -9, -8, -6, -5, -3, -2, 0, 1, 2, 4, 5, 7,
                             8, 9, 11, 12, 14, 15, 16, 18, 19, 21, 22, 23, 25, 26, 28, 29, 30, 32,
                             33, 35, 36, 37, 39, 40, 42, 43, 44, 46, 47, 49, 50, 51, 53, 54, 56, 57,
                             58, 60, 61, 63, 64, 65, 67, 68, 70, 71, 72, 74, 75, 77, 78, 79, 81, 82,
                             84, 85, 86, 88, 89, 91, 92, 93, 95, 96, 98, 99, 100, 102, 103, 105,
                             106, 107, 109, 110, 112, 113, 114, 116, 117, 119, 120, 122, 123, 124,
                             126, 127, 129, 130, 131, 133, 134, 136, 137, 138, 140, 141, 143, 144,
                             145, 147, 148, 150, 151, 152, 154, 155, 157, 158, 159, 161, 162, 164,
                             165, 166, 168, 169, 171, 172, 173, 175, 176, 178};
static int Table_fv2[256] = {-92, -91, -91, -90, -89, -88, -88, -87, -86, -86, -85, -84, -83, -83,
                             -82, -81, -81, -80, -79, -78, -78, -77, -76, -76, -75, -74, -73, -73,
                             -72, -71, -71, -70, -69, -68, -68, -67, -66, -66, -65, -64, -63, -63,
                             -62, -61, -61, -60, -59, -58, -58, -57, -56, -56, -55, -54, -53, -53,
                             -52, -51, -51, -50, -49, -48, -48, -47, -46, -46, -45, -44, -43, -43,
                             -42, -41, -41, -40, -39, -38, -38, -37, -36, -36, -35, -34, -33, -33,
                             -32, -31, -31, -30, -29, -28, -28, -27, -26, -26, -25, -24, -23, -23,
                             -22, -21, -21, -20, -19, -18, -18, -17, -16, -16, -15, -14, -13, -13,
                             -12, -11, -11, -10, -9, -8, -8, -7, -6, -6, -5, -4, -3, -3, -2, -1, 0,
                             0, 1, 2, 2, 3, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 11, 12, 12, 13, 14, 15,
                             15, 16, 17, 17, 18, 19, 20, 20, 21, 22, 22, 23, 24, 25, 25, 26, 27, 27,
                             28, 29, 30, 30, 31, 32, 32, 33, 34, 35, 35, 36, 37, 37, 38, 39, 40, 40,
                             41, 42, 42, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 50, 51, 52, 52, 53,
                             54, 55, 55, 56, 57, 57, 58, 59, 60, 60, 61, 62, 62, 63, 64, 65, 65, 66,
                             67, 67, 68, 69, 70, 70, 71, 72, 72, 73, 74, 75, 75, 76, 77, 77, 78, 79,
                             80, 80, 81, 82, 82, 83, 84, 85, 85, 86, 87, 87, 88, 89, 90, 90};
static int Table_fu1[256] = {-44, -44, -44, -43, -43, -43, -42, -42, -42, -41, -41, -41, -40, -40,
                             -40, -39, -39, -39, -38, -38, -38, -37, -37, -37, -36, -36, -36, -35,
                             -35, -35, -34, -34, -33, -33, -33, -32, -32, -32, -31, -31, -31, -30,
                             -30, -30, -29, -29, -29, -28, -28, -28, -27, -27, -27, -26, -26, -26,
                             -25, -25, -25, -24, -24, -24, -23, -23, -22, -22, -22, -21, -21, -21,
                             -20, -20, -20, -19, -19, -19, -18, -18, -18, -17, -17, -17, -16, -16,
                             -16, -15, -15, -15, -14, -14, -14, -13, -13, -13, -12, -12, -11, -11,
                             -11, -10, -10, -10, -9, -9, -9, -8, -8, -8, -7, -7, -7, -6, -6, -6, -5,
                             -5, -5, -4, -4, -4, -3, -3, -3, -2, -2, -2, -1, -1, 0, 0, 0, 1, 1, 1,
                             2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9,
                             10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16,
                             16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 22, 22,
                             22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28,
                             28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 33, 33, 33, 34, 34, 34,
                             35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40,
                             41, 41, 41, 42, 42, 42, 43, 43};
static int Table_fu2[256] = {-227, -226, -224, -222, -220, -219, -217, -215, -213, -212, -210, -208,
                             -206, -204, -203, -201, -199, -197, -196, -194, -192, -190, -188, -187,
                             -185, -183, -181, -180, -178, -176, -174, -173, -171, -169, -167, -165,
                             -164, -162, -160, -158, -157, -155, -153, -151, -149, -148, -146, -144,
                             -142, -141, -139, -137, -135, -134, -132, -130, -128, -126, -125, -123,
                             -121, -119, -118, -116, -114, -112, -110, -109, -107, -105, -103, -102,
                             -100, -98, -96, -94, -93, -91, -89, -87, -86, -84, -82, -80, -79, -77,
                             -75, -73, -71, -70, -68, -66, -64, -63, -61, -59, -57, -55, -54, -52,
                             -50, -48, -47, -45, -43, -41, -40, -38, -36, -34, -32, -31, -29, -27,
                             -25, -24, -22, -20, -18, -16, -15, -13, -11, -9, -8, -6, -4, -2, 0, 1,
                             3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 21, 23, 24, 26, 28, 30, 31, 33, 35,
                             37, 39, 40, 42, 44, 46, 47, 49, 51, 53, 54, 56, 58, 60, 62, 63, 65, 67,
                             69, 70, 72, 74, 76, 78, 79, 81, 83, 85, 86, 88, 90, 92, 93, 95, 97, 99,
                             101, 102, 104, 106, 108, 109, 111, 113, 115, 117, 118, 120, 122, 124,
                             125, 127, 129, 131, 133, 134, 136, 138, 140, 141, 143, 145, 147, 148,
                             150, 152, 154, 156, 157, 159, 161, 163, 164, 166, 168, 170, 172, 173,
                             175, 177, 179, 180, 182, 184, 186, 187, 189, 191, 193, 195, 196, 198,
                             200, 202, 203, 205, 207, 209, 211, 212, 214, 216, 218, 219, 221, 223,
                             225};

bool YV12ToBGR24_Table(unsigned char *pYUV, unsigned char *pBGR24, int width, int height) {
    if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
        return false;
    const long len = width * height;
    unsigned char *yData = pYUV;
    unsigned char *vData = &yData[len];
    unsigned char *uData = &vData[len >> 2];

    int bgr[3];
    int yIdx, uIdx, vIdx, idx;
    int rdif, invgdif, bdif;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            yIdx = i * width + j;
            vIdx = (i / 2) * (width / 2) + (j / 2);
            uIdx = vIdx;

            rdif = Table_fv1[vData[vIdx]];
            invgdif = Table_fu1[uData[uIdx]] + Table_fv2[vData[vIdx]];
            bdif = Table_fu2[uData[uIdx]];

            bgr[0] = yData[yIdx] + bdif;
            bgr[1] = yData[yIdx] - invgdif;
            bgr[2] = yData[yIdx] + rdif;

            for (int k = 0; k < 3; k++) {
                idx = (i * width + j) * 3 + k;
                if (bgr[k] >= 0 && bgr[k] <= 255)
                    pBGR24[idx] = bgr[k];
                else
                    pBGR24[idx] = (bgr[k] < 0) ? 0 : 255;
            }
        }
    }
    return true;
}

bool cropBGR(unsigned char *pBGR24, int width, int height, int x1, int y1, int x2, int y2) {
    int targetWidth = x2 - x1;
    int targetHeight = y2 - y1;
    unsigned char *smallPic = (unsigned char *) calloc(1, targetHeight * targetWidth * 3);

    unsigned char *src = pBGR24;
    unsigned char *dest = smallPic;
    for (int i = y1; i < y2 + 1; i++) {
        *src = *src + (y1 - 1) * width * 3 + x1 * 3;
        memcpy(dest, src, targetWidth);
    }
}


int Rotation90Right(unsigned char *src, unsigned char *des, int srcW, int srcH, int channel) {

    int i = 0;
    int j = 0;
    int k = 0;
    unsigned char temp = (unsigned char) 0;
    for (i = srcH - 1; i >= 0; i--) {
        for (j = 0; j < srcW; j++) {
            for (k = 0; k < channel; k++) {
                temp = src[(i * srcW + j) * channel + k];

                des[((j) * srcH + (srcH - 1 - i)) * channel + k] = temp;
            }

        }
    }
    return 0;

}


int Rotation180Right(unsigned char *src, unsigned char *des, int srcW, int srcH, int channel) {
    int i = 0;
    int j = 0;
    int k = 0;
    unsigned char temp = (unsigned char) 0;
    for (i = 0; i <= srcH - 1; i++) {
        for (j = 0; j <= srcW - 1; j++) {
            for (k = 0; k < channel; k++) {
                temp = src[(i * srcW + j) * channel + k];
                des[((srcH - 1 - i) * srcW + (srcW - 1 - j)) * channel + k] = temp;
            }
        }
    }
/*int i =0;
int j =0;
int k =0;
unsigned char temp = (unsigned char )0;
for(i = 0;i< srcH ;i++)
{
for(j = 0 ;j < srcW ; j++)
{
for(k = 0 ; k<channel; k++)
{
temp = src[(i * srcW + j) * channel + k];
des[((srcW-j-1)+j*srcH)* channel + k]= temp;
}
}
}*/
    return 0;
}


int Rotation270Right(unsigned char *src, unsigned char *des, int srcW, int srcH, int channel) {
    int i = 0;
    int j = 0;
    int k = 0;
    unsigned char temp = (unsigned char) 0;
    for (i = 0; i <= srcH - 1; i++) {
        for (j = 0; j <= srcW - 1; j++) {
            for (k = 0; k < channel; k++) {
                temp = src[(i * srcW + j) * channel + k];
                des[((srcW - 1 - j) * srcH + i) * channel + k] = temp;
//des[((srcH-1-i)*srcW + j )*channel + k];
            }
        }
    }
    return 0;
}
}

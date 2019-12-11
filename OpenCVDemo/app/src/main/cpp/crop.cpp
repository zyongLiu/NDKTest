//
// Created by liuyz on 2018/12/10.
//

#include <string.h>
#include "common/crop.h"

// 图像截取函数
int clamp_s(int value, int m_min, int m_max) {
    int mm_ret = value;
    if (value < m_min) {
        mm_ret = m_min;
    } else if (value > m_max) {
        mm_ret = m_max;
    }
    return mm_ret;
}

// 方法- 有填边的截取，如果坐标超界，超出的部分赋值为0
//data 输入图像数据
//desData 输出图像数据
// srcW 输入图像宽
// srcH 输入图像高
// desW 截取图像宽 = x1 - x0 + 1
// desH 截取图像高 = y1 - y0 + 1
// x0 y0 左上角坐标
// x1 y1 右下角坐标
// channel 通道
int cutToResultNew(unsigned char *data, unsigned char *desData, int srcW, int srcH, int desW, int desH,
               int x0, int y0, int x1, int y1, int channel) {
    int err = 0;


    int i = 0;
    int j = 0;
    int xStart = 0;
    int yStart = 0;
    int xEnd = 0;
    int yEnd = 0;


    int desXstart = 0;
    int desYstart = 0;


    xStart = x0;
    yStart = y0;
    xEnd = x1;
    yEnd = y1;

    if (xStart < 0) {
        desXstart = -xStart;
    } else {
        desXstart = 0;
    }
    if (yStart < 0) {
        desYstart = -yStart;
    } else {
        desYstart = 0;
    }
    for (i = yStart; i < yStart + desH; i++) {
        if (i < 0 || i >= srcH) {
            memset(&desData[((i - yStart) * desW + desXstart) * channel], 0,
                   (clamp_s(xEnd, 0, srcW - 1) - clamp_s(xStart, 0, srcW - 1) + 1) * channel);
        } else {
            memcpy(&desData[((i - yStart) * desW + desXstart) * channel],
                   &data[(clamp_s(i, 0, srcH - 1) * srcW + clamp_s(xStart, 0, srcW - 1)) * channel],
                   (clamp_s(xEnd, 0, srcW - 1) - clamp_s(xStart, 0, srcW - 1) + 1) * channel);

        }

    }
    return 0;
}

// 方法二
// 没有填边的图像截取， 坐标会限制在图像范围以内
/*
src 输入数据
dest 输出数据
srcW 输入图像的宽
srcH 输入图像的高
x0 截取图像左上角的x坐标
y0 截取图像左上角的y坐标
x1 截取图像右上角的x坐标
y1 截取图像右上角的y坐标

函数里面没有边界的判断，请在传入x0 x1 在0 到 srcW - 1 的范围
函数里面没有边界的判断，请在传入y0 y1 在0 到 srcH - 1 的范围
*/


int cutImageResult(unsigned char *src, unsigned char *desData, int srcW, int srcH, int x0, int y0,
                   int x1, int y1, int channel) {

    int err = 0;

    int destW = x1 - x0;
    int destH = y1 - y0;
    int i = 0;
    int destIdy = 0;

    for (i = y0; i <= y1; i++) {
        destIdy = i - y0;
        memcpy(&(desData[destIdy * destW * channel]), &(src[(i * srcW + x0) * channel]),
               sizeof(unsigned char) * channel * destW);
    }

    return 0;

}

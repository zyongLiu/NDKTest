//
// Created by liuyz on 2018/12/10.
//

int clamp_s(int value, int m_min, int m_max);

int cutToResultNew(unsigned char * data, unsigned char * desData, int srcW, int srcH, int desW, int desH,
                   int x0, int y0, int x1, int y1, int channel);

int cutImageResult(unsigned char * src, unsigned char * desData, int srcW, int srcH, int x0, int y0, int x1, int y1, int channel);




//
// Created by Nc2016 on 2019/1/13.
//

#ifndef __TEXTTOOLS_H
#define __TEXTTOOLS_H


#include "Descriptor.h"

class TextTools
{

public:
    u8* Str2Num(u8 *p, u32 *num);
    u8 *ParaSolve(u8 key, u8 *p, u32 *num);

    u8* Str2Double(u8 *p, double *d);

    void StrCpy(const char *src, u8 *dst);

    void HexCpy(u8 *src, u8 *dst, u32 len);
};

extern TextTools Tt;


#endif //HELLO_TEXTTOOLS_H

//
// Created by Nc2016 on 2019/1/13.
//

#include "TextTools.h"
#include "Msp.h"

TextTools Tt;

u8 *TextTools::Str2Num(u8 *p, u32 *num)
{
    *num = 0;
    while (*p >= '0')
    {
        *num = (*num) * 10;
        *num = (*num) + (*p) - '0';
        p++;
    }
    return p + 1;
}

u8 *TextTools::ParaSolve(u8 key, u8 *p, u32 *num)
{
    if (key != *p)return p;
    p++;
    *num = 0;
    while (*p >= '0')
    {
        *num = (*num) * 10;
        *num = (*num) + (*p) - '0';
        p++;
    }
    return p + 1;
}

u8 *TextTools::Str2Double(u8 *p, double *d)
{
    bl s=False;
    u32 tmp = 1;
    *d = 0;

    if(*p=='-'){
        *p++;
        s=True;
    }

    while (*p >= '0')
    {
        *d = (*d) * 10;
        *d = (*d) + (*p) - '0';
        p++;
    }
    if ((*p) != '.')
    {
        if(s){*d=-(*d);}
        return p + 1;
    }
    p++;
    while (*p >= '0')
    {
        tmp *= 10;
        *d = (*d) * 10;
        *d = (*d) + (*p) - '0';
        p++;
    }
    *d /= tmp;

    if(s){*d=-(*d);}
    return p + 1;
}

void TextTools::StrCpy(const char *src, u8 *dst)
{
    while (*src != '\0')
    {
        *dst = *src;
        dst++;
        src++;
    }
}

void TextTools::HexCpy(u8 *src, u8 *dst, u32 len)
{
    while (len--)
    {
        *dst = *src;
        dst++;
        src++;
    }
}

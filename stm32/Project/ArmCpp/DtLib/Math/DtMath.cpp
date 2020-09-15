//
// Created by draw on 19-5-24.
//

#include "DtMath.h"

__ccm DtMath Math;

s32 DtMath::Round(double d)
{
    s32 Tmp = d;
    if (d - Tmp >= 0.5)return Tmp + 1;
    if (d - Tmp <= -0.5)return Tmp - 1;
    return Tmp;
}

float DtMath::MedianFliter(u16 *raw, u16 len, u16 st)
{
    u16 buf[len];
    MemCopy(raw, buf, len, st);
    Sout(buf, len);
    u32 Tmp = 0;
    for (int k = 1; k < len - 1; k++)
    {
        Tmp += buf[k];
    }
    return (float)Tmp / (len - 2);
}

void DtMath::Sout(u16 *raw, u16 len, u16 st)
{
    int k, p;
    for (p = 0; p < len*st; p+=st)
    {
        for (k = p + st; k < len*st; k+=st)
        {
            if (*(raw + p) > *(raw + k))
            {
                *(raw + p) = (*(raw + p)) ^ (*(raw + k));
                *(raw + k) = (*(raw + p)) ^ (*(raw + k));
                *(raw + p) = (*(raw + p)) ^ (*(raw + k));
            }
        }
    }
}

void DtMath::MemCopy(u16 *raw, u16 *tag, u16 len, u16 s1, u16 s2)
{
    for (int k = 0; k < len; k++)
    {
        *tag = *raw;
        raw += s1;
        tag += s2;
    }
}

//
// Created by draw on 19-5-24.
//

#ifndef _DTMATH_H_
#define _DTMATH_H_

#include "Descriptor.h"


class DtMath
{

public:
    s32 Round(double d);

    float MedianFliter(u16* raw,u16 len,u16 st=1);
    void Sout(u16 *raw,u16 len,u16 st=1);
    void MemCopy(u16 *raw,u16 *tag,u16 len,u16 s1=1,u16 s2=1);
};

extern DtMath Math;




#endif //ARMCPP_BASIC_H

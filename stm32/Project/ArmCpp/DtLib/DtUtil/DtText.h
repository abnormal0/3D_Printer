//
// Created by draw on 19-5-11.
//

#ifndef _DTTEXT_H
#define _DTTEXT_H

#include "Descriptor.h"

class DtText
{
public:
    u8 Buff[128];
    u32 Len;

    DtText &operator <<(double d);
    DtText &operator <<(u32 n);
    DtText &operator <<(u8* s);
    DtText &operator <<(const char * s);
    DtText &operator <<(char c);
};



#endif //ARMCPP_DTTEXT_H

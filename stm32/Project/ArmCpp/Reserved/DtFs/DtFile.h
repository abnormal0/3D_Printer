//
// Created by draw on 19-5-6.
//

#ifndef _DTFILE_H
#define _DTFILE_H

#include "Descriptor.h"


class DtFile
{
public:
    u8 Id;
    u8 Type;
    u8 Used;
    u32 Addr;
    u32 Len;
    u8 Name[17];
};


#endif //ARMCPP_DTFILE_H

//
// Created by draw on 19-5-6.
//

#ifndef _DTFSINFO_H
#define _DTFSINFO_H

#include "Descriptor.h"


class DtFsInfo
{
public:
    u8 Name[16];
    u32 FileSize;
    u32 FileNbr;
    u32 Flag;
};


#endif //ARMCPP_DTFSINFO_H

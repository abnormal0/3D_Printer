//
// Created by draw on 19-5-19.
//

#ifndef _CFG_H
#define _CFG_H

#include "Descriptor.h"

class Cfg
{
public:
    u32 ResuX;
    u32 ResuY;
    u32 ResuZ;
    u32 ResuE;

    void Construct();
};

extern Cfg Cg;


#endif //ARMCPP_CFG_H

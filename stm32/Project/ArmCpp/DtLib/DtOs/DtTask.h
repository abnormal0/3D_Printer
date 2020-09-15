//
// Created by draw on 19-4-11.
//

#ifndef _DTTASK_H
#define _DTTASK_H

#include "Descriptor.h"

#define OS_MESS_SIZE 4096u


#define OS_MAX_WAIT  0xffffffff;


class DtTask
{
public:
    u32* sp;
    s32 sta;
    u32 mess[OS_MESS_SIZE];
    u32 R4;
    u32 R5;
    u32 R6;
    u32 R7;
    u32 R8;
    u32 R9;
    u32 R10;
    u32 R11;
    u32 R0;
    u32 R1;
    u32 R2;
    u32 R3;
    u32 R12;
    u32 LR;
    u32 PC;
    u32 xPSR;

    void Construct(void (*en)(void), void (*ex)(void));
};


#endif //ARMCPP_DTTASK_H

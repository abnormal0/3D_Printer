//
// Created by draw on 19-4-20.
//

#ifndef _SYS_H
#define _SYS_H

#include "Scb.h"
#include "Nvic.h"


class Cortex
{

public:
    void NvicPri(IRQn qn, u32 mp, u32 sp);

    void NvicGroup(Priority_Group gp);

public:
    u32 Nvic_Group;
    u32 Pll_Freq;
    u32 Sys_Freq;
    u32 Hclk_Freq;
    u32 Pclk1_Freq;
    u32 Pclk2_Freq;
    u32 Apb1_Tim_Freq;
    u32 Apb2_Tim_Freq;
    u32 Ind_Clk;
};

extern Cortex M4;


#endif //ARMCPP_SYS_H

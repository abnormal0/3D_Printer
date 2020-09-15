//
// Created by draw on 19-4-20.
//

#include "Cortex.h"

Cortex M4;

void Cortex::NvicPri(IRQn qn, u32 mp, u32 sp)
{
    if (qn < 0)
    {
        SCB->SHP[qn+12]=(mp<<Nvic_Group)|(sp<<4);
        return;
    }
    if(qn<32){
        NVIC->ISER[0]=0b1<<qn;
        NVIC->IP[qn]=(mp<<Nvic_Group)|(sp<<4);
        return;
    }
    if(qn<64){
        NVIC->ISER[1]=0b1<<(qn-32);
        NVIC->IP[qn]=(mp<<Nvic_Group)|(sp<<4);
        return;
    }
    if(qn<96){
        NVIC->ISER[2]=0b1<<(qn-64);
        NVIC->IP[qn]=(mp<<Nvic_Group)|(sp<<4);
        return;
    }
}

void Cortex::NvicGroup(Priority_Group gp)
{
    SCB->AIRCR = 0x05fa | gp;
    switch (gp){
        case Group_4:Nvic_Group=4;break;
        case Group_3:Nvic_Group=5;break;
        case Group_2:Nvic_Group=6;break;
        case Group_1:Nvic_Group=7;break;
        case Group_0:Nvic_Group=8;break;
    }
}

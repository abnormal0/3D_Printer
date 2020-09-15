//
// Created by draw on 19-4-11.
//

#include "DtOs.h"
#include "Msp.h"

DtTask *tn;
DtTask *tr;


void DtOs::Run(void)
{
    tn = 0;
    tr = tkmain;
    SCB->ICSR = 0b1 << 28;
}

void DtOs::Check(DtTask *task)
{
    tr=task;
    SCB->ICSR = 0b1 << 28;
}

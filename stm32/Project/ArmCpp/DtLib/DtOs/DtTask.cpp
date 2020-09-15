//
// Created by draw on 19-4-11.
//

#include "DtTask.h"

void DtTask::Construct(void (*en)(void), void (*ex)(void))
{
    sp=&R4;

    sta=0;

    xPSR=0x01000000U;
    PC=(u32)en;
    LR=(u32)ex;
}

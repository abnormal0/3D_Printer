//
// Created by draw on 19-4-21.
//

#include "Monitor.h"
#include "Msp.h"

Monitor Mo;


void Monitor::Start(void)
{
    TIM6->Start(74);
}

u32 Monitor::End(void)
{
    return TIM6->CNT;
}

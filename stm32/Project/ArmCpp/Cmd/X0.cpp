//
// Created by draw on 19-4-18.
//

#include "X0.h"
#include "Core.h"
#include "Dev.h"

X0::X0()
{
    n = 3;
    c[0] = 'C';
    c[1] = 'N';
    c[2] = 'P';
    pr[0] = 8;
    pr[1] = 5;
    pr[2] = 0.5;
}

void X0::Ent(u8 *p)
{
//

    ParaSolve(p);
    USART2->PrintLn((const char *) p);
}


void X0::Exe()
{
    u32 tmp=0;
    for (int k = 0; k < pr[1]; k++)
    {
        //USART2->Print("Adc%d:%d", pr[0], ADC1->GetValue(pr[0]));
        USART2->PrintLn("Hello");
        Os.mSleep(pr[2]*10000);
    }
}

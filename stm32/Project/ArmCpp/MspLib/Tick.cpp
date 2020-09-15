//
// Created by Nc2016 on 2019/1/4.
//

#include "Tick.h"
#include "Basic.h"

void Tick::Delay(u32 t)
{
    LOAD=t;
    CTRL=1;
    while (!(CTRL&0x00010000u));
    CTRL=0;
}

void Tick::Period(u32 us)
{
    LOAD=us;
}

void Tick::Ctrl(Tick_Div div, Tick_Irq irq)
{
    CTRL=div|irq;
}

void Tick::Start()
{
    CTRL|=1U;
}

bool Tick::Reloaded()
{

    return (CTRL&0x00010000u);
}

void Tick::Stop() {
    CTRL&=0xfffffffe;
}

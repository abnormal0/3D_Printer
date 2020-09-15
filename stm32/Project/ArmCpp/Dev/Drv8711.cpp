//
// Created by draw on 19-5-11.
//

#include "Drv8711.h"
#include "Core.h"
#include "Dev.h"

#define Wait Os.uWait(10)

void Drv8711::Constuct(vu32 *cs, vu32 *ck, vu32 *di, vu32 *du, vu32 *sp, vu32 *ft, vu32 *st, vu32 *dir, vu32 *step,
                       vu32 *lim)
{
    Cs = cs;
    Ck = ck;
    Di = di;
    Do = du;
    Sp = sp;
    Ft = ft;
    St = st;

    Dir = dir;
    Step = step;

    Limit = lim;
}

u16 Drv8711::Read(Drv8711_Reg addr)
{
    u16 da = (addr << 12) | (1 << 15);
    *Cs = 1;
    for (int k = 15; k >= 12; k--)
    {
        *Di = da >> k;
        *Ck = 1;
        Wait;
        *Ck = 0;
        Wait;
    }
    da = 0;
    for (int k = 11; k >= 0; k--)
    {
        *Ck = 1;
        Wait;
        da |= (*Do) << k;
        *Ck = 0;
        Wait;
    }
    *Cs = 0;
    return da;
}

void Drv8711::Write(Drv8711_Reg addr, u16 da)
{
    da = da | (addr << 12);

    *Cs = 1;
    for (int k = 15; k >= 0; k--)
    {
        *Di = da >> k;
        *Ck = 1;
        Wait;
        *Ck = 0;
        Wait;
    }
    *Cs = 0;
}

void Drv8711::Indexer(Drv8711_Indexer indexer)
{
    u16 Ct = Read(Drv8711_Reg_Ctrl);
    Ct &= ~(0b1111 << 3);
    Ct |= indexer;
    Write(Drv8711_Reg_Ctrl, Ct);
}

void Drv8711::Home(u32 p)
{
    *Dir = 0;
    while (!(*Limit))
    {
        *Step = 1;
        Os.uSleep(p);
        *Step = 0;
        Os.uSleep(p);
        //Com.Buzy();
    }

    Move(3000,p);

    *Dir = 0;
    while (!(*Limit))
    {
        *Step = 1;
        Os.uSleep(p<<2);
        *Step = 0;
        Os.uSleep(p<<2);
        //Com.Buzy();
    }
}

void Drv8711::Enable()
{
    u16 Ct = Read(Drv8711_Reg_Ctrl);
    Ct |= 1;
    Write(Drv8711_Reg_Ctrl, Ct);
}

void Drv8711::Move(s32 s, u32 p)
{
    if (s < 0)
    {
        s = -s;
        *Dir = 0;
    } else
    {
        *Dir = 1;
    }

    while (s--)
    {
        *Step=1;
        Os.uSleep(p);
        *Step=0;
        Os.uSleep(p);
    }
}

void Drv8711::Disable()
{
    u16 Ct = Read(Drv8711_Reg_Ctrl);
    Ct &= ~1;
    Write(Drv8711_Reg_Ctrl, Ct);
}

void Drv8711::Curr(float i)
{
    u8 TORQUE=0.1f*256*5/2.75f*i;
    u16 Tmp=(Read(Drv8711_Reg_Torque)&0xFF00)|TORQUE;
    Write(Drv8711_Reg_Torque, Tmp);
}



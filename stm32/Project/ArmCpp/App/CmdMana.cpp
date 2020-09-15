//
// Created by draw on 19-4-18.
//
#include "CmdMana.h"
#include "Dev.h"
#include "Core.h"
#include "DtLib.h"
#include "Msp.h"

#include "Command.h"
#include "X0.h"
#include "X10.h"
#include "G0.h"
#include "G21.h"
#include "G28.h"
#include "G90.h"
#include "G91.h"
#include "G92.h"
//#include "M20.h"
#include "M80.h"
#include "M81.h"
#include "M82.h"
#include "M84.h"
#include "M104.h"
#include "M105.h"
#include "M106.h"
#include "M107.h"
#include "M109.h"
#include "M110.h"
#include "M111.h"
#include "M114.h"
#include "M115.h"
#include "M140.h"
#include "M190.h"
#include "M201.h"
#include "M202.h"
#include "M220.h"
#include "M221.h"
#include "M270.h"
#include "M400.h"
#include "T0.h"


__ccm CmdMana Cm;

CmdMana::CmdMana()
{
    op = 0;
    tp = 0;
    len = 0;
    Line = 0;
}

void CmdMana::Offer()
{
    op++;
    if (op >= CMD_BUF_LEN) op = 0;  //CMD_BUF_LEN = 128
    len++;
    while (len >= (CMD_BUF_LEN-1))
    {
        Os.uWait(1000000);
        USART2->PrintLn("Buzy...");
    }
}

void CmdMana::Take()
{
    tp++;
    if (tp >= CMD_BUF_LEN) tp = 0;
    len--;
}

u8 *CmdMana::Check(u8 *s)
{
    u32 n;
    u8 *p;
    p = Tt.Str2Num(s, &n);
    if (n == Line)
    {
        Line++;
        return p;
    }

    return p;
}


static void GCase(u8 *p)
{
    u32 num;
    p = Tt.Str2Num(p, &num);
    switch (num)
    {
        case 0:
            (new(Cm.op) G0())->Ent(p);
            Cm.Offer();
            break;
        case 1:
            (new(Cm.op) G0())->Ent(p);
            Cm.Offer();
            break;
        case 21:(new(Cm.op) G21())->Ent(p);Cm.Offer();break;
        case 28:(new(Cm.op) G28())->Ent(p);Cm.Offer();break;
        case 90:
            (new(Cm.op) G90())->Ent(p);
            Cm.Offer();
            break;
        case 91:
            (new(Cm.op) G91())->Ent(p);
            Cm.Offer();
            break;
        case 92:
            (new(Cm.op) G92())->Ent(p);
            Cm.Offer();
            break;
        default:
            Com.Message("Cmd Error");
    }
}

static void MCase(u8 *p)
{
    u32 num;
    p = Tt.Str2Num(p, &num);
    switch (num)
    {
        //case 20:(new(Cm.op) M20())->Ent(p);Cm.Offer();break;
        case 80:(new(Cm.op) M80())->Ent(p);Cm.Offer();break;
        case 81:
            (new(Cm.op) M81())->Ent(p);
            Cm.Offer();
            break;
        case 82:
            (new(Cm.op) M82())->Ent(p);
            Cm.Offer();
            break;
        case 84:
            (new(Cm.op) M81())->Ent(p);
            Cm.Offer();
            break;
        case 104:
            (new(Cm.op) M104())->Ent(p);
            Cm.Offer();
            break;
        case 105:(new(Cm.op) M105())->Ent(p);Cm.Offer();break;
        case 106:(new(Cm.op) M106())->Ent(p);Cm.Offer();break;
        case 107:
            (new(Cm.op) M107())->Ent(p);
            Cm.Offer();
            break;
        case 109:(new(Cm.op) M109())->Ent(p);Cm.Offer();break;
        case 110:(new(Cm.op) M110())->Ent(p);Cm.Offer();break;
        case 111:(new(Cm.op) M111())->Ent(p);Cm.Offer();break;
        case 114:(new(Cm.op) M114())->Ent(p);Cm.Offer();break;
        case 115:(new(Cm.op) M115())->Ent(p);Cm.Offer();break;
        case 140:(new(Cm.op) M140())->Ent(p);Cm.Offer();break;
        case 190:(new(Cm.op) M190())->Ent(p);Cm.Offer();break;
        case 201:(new(Cm.op) M201())->Ent(p);Cm.Offer();break;
        case 202:(new(Cm.op) M202())->Ent(p);Cm.Offer();break;
        case 220:(new(Cm.op) M220())->Ent(p);Cm.Offer();break;
        case 221:(new(Cm.op) M221())->Ent(p);Cm.Offer();break;
        case 270:(new(Cm.op) M270())->Ent(p);Cm.Offer();break;
        case 400:(new(Cm.op) M400())->Ent(p);Cm.Offer();break;
        default:
            Com.Message("Cmd Error");
    }
}

static void TCase(u8 *p)
{
    u32 num;
    p = Tt.Str2Num(p, &num);
    switch (num)
    {
        case 0:
            (new(Cm.op) T0())->Ent(p);
            Cm.Offer();
            break;
        default:
            Com.Message("Cmd Error");
    }
}

static void XCase(u8 *p)
{
    u32 num;
    p = Tt.Str2Num(p, &num);
    switch (num)
    {
        case 0:
            (new(Cm.op) X0())->Ent(p);
            Cm.Offer();
            break;
        case 10:
            (new(Cm.op) X10())->Ent(p);
            Cm.Offer();
            break;
        default:
            Com.Message("Cmd Error");
    }
}


static void CodeCase(u8 *p)
{
    switch (*(p++))
    {
        case 'G':
            GCase(p);
            break;
        case 'M':
            MCase(p);
            break;
        case 'T':
            TCase(p);
            break;
        case 'X':
            XCase(p);
            break;
        default:
            Com.Message("Cmd Error");
    }
}

void CmdHandle(u8 *p)
{

    if (*p == 'N')
    {
        p = Cm.Check(p+1);

        if (p == nullptr)
        {
            Com.Message("Check Error");
            return;
        }
    }

    CodeCase(p);
}

void CmdTask(void)
{
    while (1)
    {
        if (Com.Rp == Com.Wp)
        {
            continue;
        }

        Com.ReadLine();

        CmdHandle(Com.Lin);

        Com.Lp = 0;

    }
}


void MainTask(void)
{
    while (1)
    {
        while (Cm.len == 0)
        {
            Os.mSleep(1000);
            //Io.Tog1();
        }
        //Io.Beep(1);
        cmds[Cm.tp].Exe();
        Cm.Take();
        //Io.Beep(0);
    }
}

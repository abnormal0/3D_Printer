//
// Created by draw on 19-5-11.
//
// Every file under Cmd is an instruction

#include "G0.h"
#include "Dev.h"

G0::G0()
{
    n = 5;  // Number of parameter
    c[0] = 'X';
    c[1] = 'Y';
    c[2] = 'Z';
    c[3] = 'E';
    c[4] = 'F';
    pr[0] = 4210;   // Initial position
    pr[1] = 4210;
    pr[2] = 4210;
    pr[3] = 4210;
    pr[4] = 0;
}

void G0::Ent(u8 *p)
{
    ParaSolve(p);   // Command.h
    Com.Ok();
}

void G0::Exe()
{
    double x, y, z, e;

    if (Mn.Abs)     // Motion.h
    {
        x = (pr[0] == 4210) ? Mn.X : pr[0];
        y = (pr[1] == 4210) ? Mn.Y : pr[1];
        z = (pr[2] == 4210) ? Mn.Z : pr[2];
        e = (pr[3] == 4210) ? Mn.E : pr[3];
    } else{
        x = (pr[0] == 4210) ? 0 : pr[0];
        y = (pr[1] == 4210) ? 0 : pr[1];
        z = (pr[2] == 4210) ? 0 : pr[2];
        e = (pr[3] == 4210) ? 0 : pr[3];
    }


    if (pr[4] > 0)
    {
        Mn.Speed((u32) pr[4]);
    }
    Mn.Line(x,y,z,e);
}

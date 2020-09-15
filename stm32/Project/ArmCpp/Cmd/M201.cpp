//
// Created by draw on 19-5-24.
//

#include "M201.h"
#include "Dev.h"

M201::M201()
{
    n = 4;
    c[0] = 'X';
    c[1] = 'Y';
    c[2] = 'Z';
    c[3] = 'E';
    pr[0] = 4210;
    pr[1] = 4210;
    pr[2] = 4210;
    pr[3] = 4210;
}

void M201::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void M201::Exe()
{
    Mn.Ax = (pr[0] == 4210) ? Mn.Ax : pr[0];
    Mn.Ay = (pr[1] == 4210) ? Mn.Ay : pr[1];
    Mn.Az = (pr[2] == 4210) ? Mn.Az : pr[2];
    Mn.Ae = (pr[3] == 4210) ? Mn.Ae : pr[3];
}

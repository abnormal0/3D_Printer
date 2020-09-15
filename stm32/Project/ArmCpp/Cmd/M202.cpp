//
// Created by draw on 19-5-24.
//

#include "M202.h"
#include "Dev.h"

M202::M202() {
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

void M202::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void M202::Exe()
{
    Mn.Vx = (pr[0] == 4210) ? Mn.Vx : pr[0];
    Mn.Vy = (pr[1] == 4210) ? Mn.Vy : pr[1];
    Mn.Vz = (pr[2] == 4210) ? Mn.Vz : pr[2];
    Mn.Ve = (pr[3] == 4210) ? Mn.Ve : pr[3];
}

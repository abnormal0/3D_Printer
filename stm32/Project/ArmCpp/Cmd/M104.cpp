//
// Created by draw on 19-5-11.
//

#include "M104.h"
#include "Dev.h"

M104::M104()
{
    n = 2;
    c[0] = 'T';
    c[1] = 'S';
    pr[0] = 0;
    pr[1] = 0;
}

void M104::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void M104::Exe()
{
    Pi.Ts=(float)(pr[1]);
}

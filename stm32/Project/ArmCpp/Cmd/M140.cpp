//
// Created by draw on 19-5-11.
//

#include "M140.h"
#include "Dev.h"

M140::M140()
{
    n = 1;
    c[0] = 'S';
    pr[0] = 0;
}

void M140::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void M140::Exe()
{
    Pi.Bs=(float)(pr[0]);
}

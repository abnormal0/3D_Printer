//
// Created by draw on 19-5-19.
//

#include "X10.h"
#include "Dev.h"

X10::X10()
{
    n = 2;
    c[0] = 'P';
    c[1] = 'D';
    pr[0] = 100;
    pr[1] = 2000;
}

void X10::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void X10::Exe()
{
    Pi.Kpt=(float)(pr[0]);
    Pi.Kdt=(float)(pr[1]);
}

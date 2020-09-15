//
// Created by draw on 19-5-24.
//

#include "M270.h"
#include "Dev.h"

M270::M270()
{
    n = 4;
    c[0] = 'X';
    c[1] = 'Y';
    c[2] = 'Z';
    c[3] = 'E';
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 0;
    pr[3] = 0;
}

void M270::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void M270::Exe()
{
    if (pr[0] != 0) { Mn.Mx.Curr((float) (pr[0])); }
    if (pr[1] != 0) { Mn.My.Curr((float) (pr[1])); }
    if (pr[2] != 0) { Mn.Mz.Curr((float) (pr[2])); }
    if (pr[3] != 0) { Mn.Me.Curr((float) (pr[3])); }
}


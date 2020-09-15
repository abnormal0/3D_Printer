//
// Created by draw on 19-5-11.
//

#include "G92.h"
#include "Dev.h"

G92::G92()
{
    n = 4;
    c[0] = 'X';
    c[1] = 'Y';
    c[2] = 'Z';
    c[3] = 'E';
    pr[0] = -1;
    pr[1] = -1;
    pr[2] = -1;
    pr[3] = -1;
}

void G92::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void G92::Exe()
{
    if(pr[0]>=0)Mn.SetX(pr[0]);
    if(pr[1]>=0)Mn.SetY(pr[1]);
    if(pr[2]>=0)Mn.SetZ(pr[2]);
    if(pr[3]>=0)Mn.SetE(pr[3]);
}

//
// Created by draw on 19-5-20.
//

#include "M220.h"
#include "Dev.h"

M220::M220()
{
    n=1;
    c[0]='S';
    pr[0]=100.0f;
}

void M220::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void M220::Exe()
{
    Mn.Fr=pr[0]/100.0;
}

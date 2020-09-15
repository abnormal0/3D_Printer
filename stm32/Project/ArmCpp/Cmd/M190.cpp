//
// Created by draw on 19-5-22.
//

#include "M190.h"

#include "Dev.h"
#include "Core.h"

M190::M190()
{
    n = 1;
    c[0] = 'S';
    pr[0] = 0;
}

void M190::Ent(u8 *p)
{
    ParaSolve(p);
}

void M190::Exe()
{
    Pi.Bs = (float) (pr[0]);

    while (Pi.Wb < 200)
    {
        Os.mSleep(3000);
        Com.Text<<"T:"<<Pi.T<<' ';
        Com.Text<<"B:"<<Pi.B<<" buzy";
        Com.Flush();
    }
    Com.Ok();
}


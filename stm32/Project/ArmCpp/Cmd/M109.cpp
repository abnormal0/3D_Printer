//
// Created by draw on 19-5-11.
//

#include "M109.h"
#include "Dev.h"
#include "Core.h"

M109::M109()
{
    n = 2;
    c[0] = 'T';
    c[1] = 'S';
    pr[0] = 0;
    pr[1] = 0;
}

void M109::Ent(u8 *p)
{
    ParaSolve(p);
}

void M109::Exe()
{
    Pi.Ts=(float)(pr[1]);
    while (Pi.Wt < 200)
    {
        Os.mSleep(3000);
        Com.Text<<"T:"<<Pi.T<<' ';
        Com.Text<<"B:"<<Pi.B<<" buzy";
        Com.Flush();
    }
    Com.Ok();
}

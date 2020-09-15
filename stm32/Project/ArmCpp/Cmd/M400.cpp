//
// Created by draw on 19-5-26.
//

#include "M400.h"
#include "Dev.h"
#include "Core.h"

M400::M400() {
    n=2;
    c[0]='P';
    c[1]='N';
    pr[0]=3000;
    pr[1]=1.0;
}

void M400::Ent(u8 *p)
{
    ParaSolve(p);
    Com.Ok();
}

void M400::Exe()
{
    for (int k=0;k<pr[1];k++){
        Io.Beep(True);
        Os.mSleep(pr[0]*5);
        Io.Beep(False);
        Os.mSleep(pr[0]*5);
    }

}

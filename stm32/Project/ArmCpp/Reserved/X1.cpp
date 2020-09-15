//
// Created by draw on 19-4-18.
//

#include "X1.h"
#include "Main.h"

X1::X1()
{
    n=1;
    c[0]='F';
    pr[0]=0;
}

void X1::Ent(u8 *p)
{
    ParaSolve(p);
}

void X1::Exe()
{
    DtFile f;
    if (Fs.Index(&f, (u32)pr[0]))
    {
        USART2->Print("File Addr:%d", f.Addr);
    } else
    {
        USART2->Print("Open Fail");
    }
}

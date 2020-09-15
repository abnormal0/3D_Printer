//
// Created by Nc2016 on 2019/1/13.
//

#include "Command.h"
#include "Msp.h"
#include "TextTools.h"

__ccm Command cmds[CMD_BUF_LEN];

void Command::ParaSolve(u8 *p)
{
    for (int k = 0; k < n; k++)
    {
        if (*p == c[k])
        {
            p++;
            p = Tt.Str2Double(p, &(pr[k]));
            if (*p == '\r')return;
            if (*p == '\n')return;
            if (*p == '\0')return;
            ParaSolve(p);
        }
    }
    p++;
}

void *Command::operator new(u32 size, u32 pos)
{
    //USART2->Print("New:%d",pos);
    return &(cmds[pos]);
}


void Command::Ent(u8 *p)
{

}

void Command::Exe()
{

}
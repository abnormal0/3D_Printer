//
// Created by Nc2016 on 2019/1/13.
//

#ifndef __COMMAND_H
#define __COMMAND_H

#include "Descriptor.h"

class Command
{
public:
    u8 n;
    u8 c[7];
    double pr[7];

    void ParaSolve(u8* p);
    void * operator new(u32 size, u32 pos);

    virtual void Ent(u8* p);
    virtual void Exe();
};

#define CMD_BUF_LEN 128
extern Command cmds[];

#endif

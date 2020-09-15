//
// Created by Nc2016 on 2019/1/5.
//

#include "Flash.h"

void Flash::WaitCycles(u32 cs)
{
    ACR=(ACR&0xfffffff8)|cs;
}

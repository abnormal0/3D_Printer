//
// Created by draw on 19-5-11.
//

#ifndef _COREOS_H
#define _COREOS_H

#include "DtLib.h"


class CoreOs:public DtOs
{
public:
    void Run(void) override;

public:
    DtTask MTask;
    DtTask CTask;

    void mSleep(u32 ms);
    void uWait(u32 us);

    void uSleep(u32 us);
};

extern CoreOs Os;


#endif //ARMCPP_COREOS_H

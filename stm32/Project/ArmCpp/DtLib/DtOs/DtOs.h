//
// Created by draw on 19-4-11.
//

#ifndef _DTOS_H
#define _DTOS_H

#include "DtTask.h"

class DtOs
{
public:
    DtTask *tkmain;
    DtTask *tkcmd;

    virtual void Run(void);

    void Check(DtTask *task);
};


#endif //ARMCPP_DTOS_H

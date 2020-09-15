//
// Created by draw on 19-5-6.
//

#ifndef _DTFS_H
#define _DTFS_H

#include "Descriptor.h"
#include "DtFsInfo.h"
#include "DtFile.h"

class DtFs
{
public:
    u8 Buff[512];
    DtFsInfo FInfo;

public:
    virtual void Load();

    bl Check(void);
    void Format(u32 sz, u32 fn);
    bl Index(DtFile *f,u8 i);

protected:
    virtual void Read(u32 addr);
    virtual void Erase(u32 addr);
    virtual void Write(u32 addr);
};


#endif //ARMCPP_DTFS_H

//
// Created by draw on 19-5-6.
//

#ifndef _APPFS_H
#define _APPFS_H

#include "DtFs.h"


class AppFs:public DtFs
{
public:
    void Load() override;
    
protected:
    void Read(u32 addr) override;

    void Erase(u32 addr) override;

    void Write(u32 addr) override;

};

extern AppFs Fs;

#endif //ARMCPP_APPFS_H

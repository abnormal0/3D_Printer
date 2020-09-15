//
// Created by draw on 19-5-24.
//

#ifndef _M201_H
#define _M201_H

#include "Command.h"


class M201:public Command
{
public:
    M201();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M201_H

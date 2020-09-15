//
// Created by draw on 19-5-24.
//

#ifndef _M202_H
#define _M202_H

#include "Command.h"


class M202:public Command
{
public:
    M202();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M202_H

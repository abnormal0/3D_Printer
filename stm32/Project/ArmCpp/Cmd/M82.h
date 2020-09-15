//
// Created by draw on 19-5-11.
//

#ifndef _M82_H
#define _M82_H

#include "Command.h"


class M82:public Command
{
public:
    M82();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M82_H

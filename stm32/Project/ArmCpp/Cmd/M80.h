//
// Created by draw on 19-5-20.
//

#ifndef _M80_H
#define _M80_H

#include "Command.h"


class M80:public Command
{
public:
    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M80_H

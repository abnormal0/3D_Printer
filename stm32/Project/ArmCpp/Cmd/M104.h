//
// Created by draw on 19-5-11.
//

#ifndef _M104_H
#define _M104_H

#include "Command.h"


class M104:public Command
{
public:
    M104();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M104_H

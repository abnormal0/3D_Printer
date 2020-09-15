//
// Created by draw on 19-5-22.
//

#ifndef _M190_H
#define _M190_H

#include "Command.h"


class M190:public Command
{
public:
    M190();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M190_H

//
// Created by draw on 19-5-19.
//

#ifndef _X10_H
#define _X10_H

#include "Command.h"


class X10:public Command
{
public:
    X10();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_X10_H

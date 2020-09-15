//
// Created by draw on 19-4-18.
//

#ifndef _X1_H
#define _X1_H

#include "Main.h"


class X1:public Command
{
public:
    X1();

    void Ent(u8 *p) override;

    void Exe() override;
};


#endif //ARMCPP_X1_H

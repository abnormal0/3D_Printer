//
// Created by draw on 19-4-18.
//

#ifndef _X0_H
#define _X0_H


#include "Command.h"

class X0: public Command
{
public:
    X0();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_X0_H

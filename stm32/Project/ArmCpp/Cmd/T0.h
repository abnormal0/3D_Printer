//
// Created by draw on 19-5-11.
//

#ifndef _T0_H
#define _T0_H

#include "Command.h"


class T0:public Command
{
public:
    T0();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_T0_H

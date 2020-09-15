//
// Created by draw on 19-5-20.
//

#ifndef _M220_H
#define _M220_H

#include "Command.h"


class M220:public Command
{
public:
    M220();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M220_H

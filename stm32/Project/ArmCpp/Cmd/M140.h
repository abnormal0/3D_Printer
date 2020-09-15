//
// Created by draw on 19-5-11.
//

#ifndef _M140_H
#define _M140_H

#include "Command.h"


class M140:public Command
{
public:
    M140();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M140_H

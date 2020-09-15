//
// Created by draw on 19-5-11.
//

#ifndef _M106_H
#define _M106_H

#include "Command.h"


class M106:public Command
{
public:
    M106();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M106_H

//
// Created by draw on 19-5-26.
//

#ifndef _M400_H
#define _M400_H

#include "Command.h"


class M400:public Command
{
public:
    M400();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M400_H

//
// Created by draw on 19-5-11.
//

#ifndef _M107_H
#define _M107_H

#include "Command.h"


class M107:public Command
{
public:
    M107();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M107_H

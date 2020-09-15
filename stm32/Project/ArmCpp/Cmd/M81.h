//
// Created by draw on 19-5-20.
//

#ifndef _M81_H
#define _M81_H

#include "Command.h"


class M81:public Command
{
public:
    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_M81_H

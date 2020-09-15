//
// Created by draw on 19-5-20.
//

#ifndef _M114_H
#define _M114_H

#include "Command.h"


class M114:public Command
{
public:
    void Ent(u8 *p) override;
};


#endif //ARMCPP_M114_H

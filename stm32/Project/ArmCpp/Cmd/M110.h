//
// Created by draw on 19-5-21.
//

#ifndef _M110_H
#define _M110_H

#include "Command.h"


class M110:public Command
{
public:
    void Ent(u8 *p) override;

};


#endif //ARMCPP_M110_H

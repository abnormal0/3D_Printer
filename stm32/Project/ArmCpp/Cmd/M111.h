//
// Created by draw on 19-5-21.
//

#ifndef _M111_H
#define _M111_H

#include "Command.h"


class M111:public Command
{
public:
    void Ent(u8 *p) override;

};


#endif //ARMCPP_M111_H

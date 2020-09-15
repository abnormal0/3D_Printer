//
// Created by draw on 19-5-23.
//

#ifndef _G21_H
#define _G21_H

#include "Command.h"


class G21:public Command
{
public:
    void Ent(u8 *p) override;

};


#endif //ARMCPP_G21_H

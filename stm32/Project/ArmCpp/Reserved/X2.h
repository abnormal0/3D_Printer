//
// Created by draw on 19-5-5.
//

#ifndef _X2_H
#define _X2_H


#include "Main.h"

class X2: public Command
{
public:
    X2();

    void Ent(u8 *p) override;

    void Exe() override;

};


#endif //ARMCPP_X2_H

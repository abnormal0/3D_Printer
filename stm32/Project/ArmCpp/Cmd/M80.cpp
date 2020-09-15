//
// Created by draw on 19-5-20.
//

#include "M80.h"
#include "Dev.h"

void M80::Ent(u8 *p)
{
    Com.Ok();
}

void M80::Exe()
{
    Mn.Mx.Enable();
    Mn.My.Enable();
    Mn.Mz.Enable();
    Mn.Me.Enable();
}

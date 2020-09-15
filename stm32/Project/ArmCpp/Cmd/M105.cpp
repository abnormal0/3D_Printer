//
// Created by draw on 19-5-15.
//

#include "M105.h"
#include "Dev.h"
#include "DtLib.h"



void M105::Ent(u8 *p)
{
    Com.Text<<"ok ";
    Com.Text<<"T:"<<Pi.T<<' ';
    Com.Text<<"B:"<<Pi.B;
    Com.Flush();
}

void M105::Exe()
{
}

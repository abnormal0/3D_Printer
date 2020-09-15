//
// Created by draw on 19-5-20.
//

#include "M114.h"
#include "Dev.h"
#include "DtLib.h"


void M114::Ent(u8 *p)
{
    Com.Text<<"X:"<<Mn.X<<' ';
    Com.Text<<"Y:"<<Mn.Y<<' ';
    Com.Text<<"Z:"<<Mn.Z<<' ';
    Com.Text<<"E:"<<Mn.E;
    Com.Flush();
}



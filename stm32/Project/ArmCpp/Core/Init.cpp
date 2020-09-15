//
// Created by draw on 19-4-10.
//
#include "Descriptor.h"
#include "Dev.h"
#include "DtLib.h"

#include "CoreOs.h"

static void DataInit(void);

static void TaskInit(void);

static void DevInit(void);

void Delay(u32 n)
{
    volatile u32 t = 1000000;
    while (--t);
}


extern "C"
void Init(void)
{
    DevInit();
    DataInit();
    TaskInit();
}

void DevInit(void)
{
    Com.Construct();

    Io.Construct();

    Mn.Constuct();
}


void DataInit(void)
{
    Cg.Construct();
}

void TaskInit(void)
{
    Pi.Run();
    Os.Run();
}

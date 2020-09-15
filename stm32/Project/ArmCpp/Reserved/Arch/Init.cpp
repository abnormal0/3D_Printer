//
// Created by draw on 19-4-10.
//
#include "Main.h"

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

}


void DataInit(void)
{
    Fs.Load();
}

void TaskInit(void)
{
    USART2->PrintLn("PID Starting...");
    pid.Start();
    USART2->PrintLn("Task Starting...");
    Os.Run();
}

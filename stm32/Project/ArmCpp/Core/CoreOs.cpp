//
// Created by draw on 19-5-11.
//

#include "CoreOs.h"
#include "Msp.h"

__ccm CoreOs Os;

void MainTask(void);
void CmdTask(void);
void ExitTask(void);


extern "C"
void TIM7_IRQHandler(void)
{
    TIM7->SR=0;
    Os.Check(Os.tkmain);
}

void CoreOs::Run(void)
{
    MTask.Construct(MainTask,ExitTask);
    CTask.Construct(CmdTask,ExitTask);
    tkmain=&MTask;
    tkcmd=&CTask;
    DtOs::Run();
}

void CoreOs::mSleep(u32 ms)
{
    asm("cpsid i\n");
    TIM7->Sleep(7199, ms);
    Check(tkcmd);
    asm("cpsie i\n");
}

void CoreOs::uWait(u32 us)
{
    TICK->Delay(us*144);
}

void CoreOs::uSleep(u32 us)
{
    asm("cpsid i\n");
    TIM7->Sleep(71, us);
    Check(tkcmd);
    asm("cpsie i\n");
}

//
// Created by draw on 19-5-6.
//

#include "AppFs.h"
#include "Main.h"

__ccm AppFs Fs;

void AppFs::Load()
{
    TICK->Delay(288000);
    if (Tf.SetUp())
    {
        USART2->PrintLn("TF Card Init Ok!");
        USART2->Print("SD Block Number %d", Tf.BlockNbr);
        USART2->Print("SD Block Size %d", Tf.BlockSize);
        USART2->Print("SD Capacity %dM", Tf.BlockNbr / 1024 * Tf.BlockSize / 1024);
    } else
    {
        USART2->PrintLn("TF Card Init Fault!");
        while (1);
    }
}

void AppFs::Read(u32 addr)
{
    Tf.ReadBlock((u32*)Buff,addr);
}

void AppFs::Erase(u32 addr)
{
    Tf.Erase(addr,addr+1);
}

void AppFs::Write(u32 addr)
{
    Tf.Erase(addr,addr+1);
    TICK->Delay(0xFFFFFF);
    USART2->Push('-');
    TICK->Delay(0xFFFFFF);
    USART2->Push('-');
    TICK->Delay(0xFFFFFF);
    USART2->Push('-');
    TICK->Delay(0xFFFFFF);
    USART2->Push('-');
    Tf.WriteBlock((u32*)Buff,addr);
}

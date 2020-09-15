//
// Created by draw on 19-5-11.
//

#include <stdio.h>
#include <cstdarg>
#include "Comm.h"

Comm Com;

extern "C"
void USART2_IRQHandler(void)
{

    USART2->Clean(Status_Idle);

    Com.Wp = COM_RX_SIZE - (DMA1->DS5.NDTR);

}

void Comm::Construct(void)
{
    Lp = 0;
    Wp = 0;
    Rp = 0;
    Len = 0;
    UART = USART2;

    DMA1->DS5.DateNum(COM_RX_SIZE);
    DMA1->DS5.Mem0Addr((u32) (Rxb));
    DMA1->DS5.PerAddr((u32) &(USART2->DR));

    DMA1->DS5.Select(Ch4);
    DMA1->DS5.Priority(Priority0);
    DMA1->DS5.MemSet(Mem8, Mem_Inc);
    DMA1->DS5.PerSet(Per8, Per_Fix);
    DMA1->DS5.Dir(Per_To_Mem);
    DMA1->DS5.Circular(True);
    DMA1->DS5.FlowCtrl(Dma_Ctrl);
    DMA1->DS5.Start();

    UART->Reset();
    UART->Baud(115200);

    UART->CR1 |= 1 << 4;
    UART->CR3 |= 1 << 6;

    UART->Enable(Tx_Rx_Both);
    UART->PrintLn("Comm Init...");
}

void Comm::Ok(void)
{
    UART->PrintLn("ok");
}

void Comm::Buzy()
{
    UART->PrintLn("Buzy...");
}

//void Comm::Debug(const char *s, ...)
//{
//    char buffer[64];
//    va_list args;
//    va_start (args, s);
//    vsprintf(buffer, s, args);
//    UART->PrintLn(buffer);
//    va_end (args);
//}

void Comm::Flush()
{
    Txb[Len]=0;
    UART->PrintLn(Txb);
    Len = 0;
}

void Comm::Message(const char *s)
{
    UART->PrintLn(s);
}

void Comm::ReadLine()
{
    while (Rp != Wp)
    {

        if (Rxb[Rp] == '\n')
        {
            Rp++;
            if (Rp == COM_RX_SIZE)
            {
                Rp = 0;
            }
            break;
        }
        Lin[Lp++] = Rxb[Rp++];
        if (Rp == COM_RX_SIZE)
        {
            Rp = 0;
        }
    }

    Lin[Lp++]='\0';

}



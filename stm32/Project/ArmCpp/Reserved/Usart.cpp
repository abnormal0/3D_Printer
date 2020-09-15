//
// Created by Nc2016 on 2019/1/5.
//

#include <cstdio>
#include <cstdarg>
#include "Usart.h"
#include "Cortex.h"

void Usart::Baud(u32 b)
{
    float div = (float) (M4.Pclk1_Freq >> 4) / (float) b;
    u32 div_m = (u32) div;
    u32 div_f = (u32) ((div - div_m) * 16);

    BRR = ((div_m << 4) + div_f) & 0xffff;
}

void Usart::Reset()
{
    CR1 = 0U;
    CR2 = 0U;
    CR3 = 0U;
    //GTPR=1U;
}

void Usart::Enable(Use_Mode mode)
{
    switch (mode)
    {
        case Tx_Rx_Both:
            CR1 |= 0x200cU;
            break;
        case Tx_Only:
            CR1 |= 0x2008U;
            break;
        case Rx_Only:
            CR1 |= 0x2004U;
            break;
    }
}

void Usart::PrintLn(const char *s)
{
    while ((*s) != '\0')
    {
        while (!(SR & 0x80));
        DR = (u8) (*(s++));
    }
    while (!(SR & 0x80));
    DR = '\r';
    while (!(SR & 0x80));
    DR = '\n';
}

void Usart::Clean(Usart_Status s)
{
    volatile u32 tmp;
    switch (s)
    {
        case Status_Idle:
            tmp = SR;
            tmp = DR;
            break;
    }
}

void Usart::Print(const char *s, ...)
{
    char buffer[64];
    va_list args;
    va_start (args, s);
    vsprintf(buffer, s, args);
    PrintLn(buffer);
    va_end (args);
}

void Usart::SendHex(u8 *hex, u32 len)
{
    while (len--)
    {
        while (!(SR & 0x80));
        DR = (u8) (*(hex++));
    }
}

void Usart::Push(char c)
{
    while (!(SR & 0x80));
    DR = (u8) (c);
}

//
// Created by Nc2016 on 2019/1/5.
//

#ifndef __USART_H
#define __USART_H

#include "Descriptor.h"

enum Use_Mode
{
    Tx_Rx_Both = 0,
    Tx_Only = 1,
    Rx_Only = 2,
};

enum Usart_Status
{
    Status_Idle = 0,
};


class Usart
{
public:
    __IO u32 SR;         /*!< USART Status register,                   Address offset: 0x00 */
    __IO u32 DR;         /*!< USART Data register,                     Address offset: 0x04 */
    __IO u32 BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
    __IO u32 CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
    __IO u32 CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
    __IO u32 CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
    __IO u32 GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
    void Baud(u32 b);

    void Reset();

    void Enable(Use_Mode mode);

    void PrintLn(const char *s);

    void Clean(Usart_Status s);

    void Print(const char* s,...);

    void SendHex(u8 *hex, u32 len);

    void Push(char c);
};

#define USART1                ((Usart *) 0x40011000U)
#define USART2                ((Usart *) 0x40004400U)
#define UART5                 ((Usart *) 0x40005000U)


#endif //HELLO_USART_H

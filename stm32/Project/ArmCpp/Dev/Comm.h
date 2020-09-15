//
// Created by draw on 19-5-11.
//

#ifndef _COMM_H
#define _COMM_H

#include <DtUtil/DtText.h>
#include "Descriptor.h"
#include "Msp.h"

#define COM_RX_SIZE 1024u
#define COM_LINE_SIZE 64u
#define COM_TX_SIZE 128u

class Comm
{
public:
    u8 Rxb[COM_RX_SIZE];
    u8 Lin[COM_LINE_SIZE];
    u32 Lp;
    u32 Wp;
    u32 Rp;
    union
    {
        DtText Text;
        struct
        {
            u8 Txb[COM_TX_SIZE];
            u32 Len;
        };
    };
    Usart *UART;

    void Construct(void);

    void Ok(void);

    void Buzy();

    void Flush();

    void Message(const char *s);

    void ReadLine();
};

extern Comm Com;


#endif //ARMCPP_COMM_H

//
// Created by draw on 19-5-4.
//

#include "TFCard.h"
#include "Msp.h"

TFCard Tf;
u8 TF_Buff[512];

void TFCard::SolveInfo()
{
    u32 tmp = 0U;
    u32 DeviceSize;
    u8 DeviceSizeMul;
    u8 RdBlockLen;


    /* Byte 5 */
    tmp = (CSD[1U] & 0x00FF0000U) >> 16U;
    RdBlockLen = (u8) (tmp & 0x0FU);

    /* Byte 6 */
    tmp = (CSD[1U] & 0x0000FF00U) >> 8U;

    DeviceSize = (tmp & 0x03U) << 10U;

    /* Byte 7 */
    tmp = (u8) (CSD[1U] & 0x000000FFU);
    DeviceSize |= (tmp) << 2U;

    /* Byte 8 */
    tmp = (u8) ((CSD[2U] & 0xFF000000U) >> 24U);
    DeviceSize |= (tmp & 0xC0U) >> 6U;


    /* Byte 9 */
    tmp = (u8) ((CSD[2U] & 0x00FF0000U) >> 16U);

    DeviceSizeMul = (tmp & 0x03U) << 1U;
    /* Byte 10 */
    tmp = (u8) ((CSD[2U] & 0x0000FF00U) >> 8U);
    DeviceSizeMul |= (tmp & 0x80U) >> 7U;

    BlockNbr = (DeviceSize + 1U);
    BlockNbr *= (1U << (DeviceSizeMul + 2U));
    BlockSize = 1U << (RdBlockLen);
}

bl TFCard::SetUp()
{
    if(SDIO->Command(0, 0, Sdio_Res_No) != Sdio_Cmd_Sent)return False;
    if(SDIO->Command(8, 0x1AAU, Sdio_Res_Short) != Sdio_Cmd_Rend)return False;
    while (1)
    {
        SDIO->Command(55, 0, Sdio_Res_Short);
        SDIO->Command(41, 0xC0100000, Sdio_Res_Short);
        if (SDIO->RESP1 & (0b1 << 31)) break;
    }
    if(SDIO->Command(2, 0, Sdio_Res_Long) != Sdio_Cmd_Rend)return False;
    if(SDIO->Command(3, 0, Sdio_Res_Short) != Sdio_Cmd_Rend)return False;
    RCA = SDIO->RESP1;
    if(SDIO->Command(9, RCA, Sdio_Res_Long) != Sdio_Cmd_Rend)return False;
    CSD[0] = SDIO->RESP1;
    CSD[1] = SDIO->RESP2;
    CSD[2] = SDIO->RESP3;
    CSD[3] = SDIO->RESP4;
    SolveInfo();
    if(SDIO->Command(7, RCA, Sdio_Res_Short) != Sdio_Cmd_Rend)return False;
    if(SDIO->Command(55, RCA, Sdio_Res_Short) != Sdio_Cmd_Rend)return False;
    if(SDIO->Command(6, 2, Sdio_Res_Short) != Sdio_Cmd_Rend)return False;
    if(SDIO->Command(16, 512, Sdio_Res_Short) != Sdio_Cmd_Rend)return False;
    return True;
}


void TFCard::ReadBlock(u32 *buf, u32 addr)
{
    SDIO->Command(17, addr<<9, Sdio_Res_Short);
    SDIO->DCTRL = (9 << 4) | 0b11;
    while (!(SDIO->STA & (0x32A)))
    {
        if (SDIO->STA & (0b1 << 15))
        {
            for (int k = 0; k < 8; k++)
            {
                *buf = SDIO->FIFO;
                buf++;
            }
        }
    }
    SDIO->ICR=0x7FFU;
}

void TFCard::WriteBlock(u32 *data, u32 addr)
{
    SDIO->Command(24, addr<<9, Sdio_Res_Short);
    SDIO->DCTRL = (9 << 4) | 0b1;
    while (!(SDIO->STA & (Sdio_Fifo_Under|Sdio_Data_Fail|Sdio_Data_Out|Sdio_Data_End|Sdio_Start_Error)))
    {
        if (SDIO->STA & (Sdio_Txfifo_He))
        {
            for (int k = 0; k < 8; k++)
            {
                SDIO->FIFO=*data;
                data++;
            }
        }
    }
    SDIO->ICR=0x7FFU;
}

void TFCard::Erase(u32 s, u32 e)
{
    SDIO->Command(32, s<<9, Sdio_Res_Short);
    SDIO->Command(33, e<<9, Sdio_Res_Short);
    SDIO->Command(38, 0, Sdio_Res_Short);
    SDIO->ICR=0x7FFU;
}


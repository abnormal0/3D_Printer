//
// Created by draw on 19-5-3.
//

#ifndef _SDIO_H
#define _SDIO_H

#include "Descriptor.h"

enum Sdio_State{
    Sdio_Cmd_Fail=(0b1<<0),
    Sdio_Data_Fail=(0b1<<1),
    Sdio_Cmd_Out=(0b1<<2),
    Sdio_Data_Out=(0b1<<3),
    Sdio_Fifo_Under=(0b1<<4),
    Sdio_Fifo_Over=(0b1<<5),
    Sdio_Cmd_Rend=(0b1<<6),
    Sdio_Cmd_Sent=(0b1<<7),
    Sdio_Data_End=(0b1<<8),
    Sdio_Start_Error=(0b1<<9),
    Sdio_Data_Check=(0b1<<10),
    Sdio_Cmd_Act=(0b1<<11),
    Sdio_Tx_Act=(0b1<<12),
    Sdio_Rx_Act=(0b1<<13),
    Sdio_Txfifo_He=(0b1<<14),
    Sdio_Rxfifo_Hf=(0b1<<15),
    Sdio_Txfifo_Of=(0b1<<16),
    Sdio_Rxfifo_Of=(0b1<<17),
    Sdio_Txfifo_E=(0b1<<18),
    Sdio_Rxfifo_E=(0b1<<19),
    Sdio_TxData_Vl=(0b1<<20),
    Sdio_RxData_Vl=(0b1<<21),
    Sdio_In=(0b1<<22),
    Sdio_Ce=(0b1<<22),
};

enum Sdio_Res_Type{
    Sdio_Res_No=0b00<<6,
    Sdio_Res_Short=0b01<<6,
    Sdio_Res_Long=0b11<<6,
};

enum Sdio_Bus_Wide
{
    Sdio_Bus_1b = 0b00 << 11,
    Sdio_Bus_4b = 0b01 << 11,
    Sdio_Bus_8b = 0b10 << 11,
};

class SdioCmd
{
public:
    u32 Arg;
    u32 Cmd;

    bl Wait;
    bl Cpsm;
    Sdio_Res_Type Resp;
};

class Sdio
{
public:
    __IO u32 POWER;                 /*!< SDIO power control register,    Address offset: 0x00 */
    __IO u32 CLKCR;                 /*!< SDI clock control register,     Address offset: 0x04 */
    __IO u32 ARG;                   /*!< SDIO argument register,         Address offset: 0x08 */
    __IO u32 CMD;                   /*!< SDIO command register,          Address offset: 0x0C */
    __IO const u32 RESPCMD;        /*!< SDIO command response register, Address offset: 0x10 */
    __IO const u32 RESP1;          /*!< SDIO response 1 register,       Address offset: 0x14 */
    __IO const u32 RESP2;          /*!< SDIO response 2 register,       Address offset: 0x18 */
    __IO const u32 RESP3;          /*!< SDIO response 3 register,       Address offset: 0x1C */
    __IO const u32 RESP4;          /*!< SDIO response 4 register,       Address offset: 0x20 */
    __IO u32 DTIMER;                /*!< SDIO data timer register,       Address offset: 0x24 */
    __IO u32 DLEN;                  /*!< SDIO data length register,      Address offset: 0x28 */
    __IO u32 DCTRL;                 /*!< SDIO data control register,     Address offset: 0x2C */
    __IO const u32 DCOUNT;         /*!< SDIO data counter register,     Address offset: 0x30 */
    __IO const u32 STA;            /*!< SDIO status register,           Address offset: 0x34 */
    __IO u32 ICR;                   /*!< SDIO interrupt clear register,  Address offset: 0x38 */
    __IO u32 MASK;                  /*!< SDIO mask register,             Address offset: 0x3C */
    u32 RESERVED0[2];          /*!< Reserved, 0x40-0x44                                  */
    __IO const u32 FIFOCNT;        /*!< SDIO FIFO counter register,     Address offset: 0x48 */
    u32 RESERVED1[13];         /*!< Reserved, 0x4C-0x7C                                  */
    __IO u32 FIFO;                  /*!< SDIO data FIFO register,        Address offset: 0x80 */
public:
    void ClockDiv(u8 clk);

    void RiEdge(bl b);

    void ClkPass(bl b);

    void PowerSave(bl b);

    void BusWide(Sdio_Bus_Wide wide);

    void FlowCtrl(bl b);

    void ClkOn();

    void PowerOn();

    void SendCmd(SdioCmd *cmd);

    Sdio_State CheckCmdRespNone();

    Sdio_State CheckCmdResp7();

    Sdio_State CheckCmdResp1();

    Sdio_State CheckCmdResp3();

    Sdio_State CheckCmdResp2();

    Sdio_State CheckCmdResp6();

    Sdio_State Command(u8 cmd, u32 arg, Sdio_Res_Type resp);
};


#define SDIO                 ((Sdio *) 0x40012C00U)

extern SdioCmd TCmd;

#endif //ARMCPP_SDIO_H

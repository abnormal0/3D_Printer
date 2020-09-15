//
// Created by draw on 19-5-3.
//

#include "Sdio.h"

SdioCmd TCmd;

void Sdio::ClockDiv(u8 clk)
{
    CLKCR &= ~0b11111111;
    CLKCR |= clk;
}

void Sdio::RiEdge(bl b)
{
    if (b)CLKCR &= ~(0b1 << 13);
    else CLKCR |= 0b1 << 13;
}

void Sdio::ClkPass(bl b)
{
    if (b)CLKCR |= 0b1 << 10;

    else CLKCR &= ~(0b1 << 10);
}

void Sdio::PowerSave(bl b)
{
    if (b)CLKCR |= 0b1 << 9;

    else CLKCR &= ~(0b1 << 9);
}

void Sdio::BusWide(Sdio_Bus_Wide wide)
{
    CLKCR &= ~(0b11 << 11);
    CLKCR |= wide;
}

void Sdio::FlowCtrl(bl b)
{
    if (b)CLKCR |= 0b1 << 14;

    else CLKCR &= ~(0b1 << 14);
}

void Sdio::ClkOn()
{
    CLKCR |= 0b1 << 8;
}

void Sdio::PowerOn()
{
    POWER = 0b11;
}

void Sdio::SendCmd(SdioCmd *cmd)
{
    u32 tmp;
    ARG = cmd->Arg;
    tmp = cmd->Cmd;
    tmp |= cmd->Resp;
    if (cmd->Wait)
    {
        tmp |= 0b1 << 8;
    } else
    {
        tmp &= ~(0b1 << 8);
    }
    if (cmd->Cpsm)
    {
        tmp |= 0b1 << 10;
    } else
    {
        tmp &= ~(0b1 << 10);
    }
    this->CMD = tmp;
}

Sdio_State Sdio::CheckCmdRespNone()
{
    while (!(STA & Sdio_Cmd_Sent))
    {
        if (STA & Sdio_Cmd_Out)
        {
            return Sdio_Cmd_Out;
        }
    }
    ICR = 0x5FFU;
    return Sdio_Cmd_Sent;
}

Sdio_State Sdio::CheckCmdResp7()
{
    while (!(STA & Sdio_Cmd_Rend))
    {
        if (STA & Sdio_Cmd_Out)
        {
            ICR = Sdio_Cmd_Out;
            return Sdio_Cmd_Out;
        }
        if (STA & Sdio_Cmd_Fail)
        {
            ICR = Sdio_Cmd_Fail;
            return Sdio_Cmd_Fail;
        }
    }
    ICR = Sdio_Cmd_Rend;
    return Sdio_Cmd_Rend;
}

Sdio_State Sdio::CheckCmdResp1()
{
    while (!(STA & Sdio_Cmd_Rend))
    {
        if (STA & Sdio_Cmd_Out)
        {
            ICR = Sdio_Cmd_Out;
            return Sdio_Cmd_Out;
        }
        if (STA & Sdio_Cmd_Fail)
        {
            ICR = Sdio_Cmd_Fail;
            return Sdio_Cmd_Fail;
        }
    }
    ICR = Sdio_Cmd_Rend;
    return Sdio_Cmd_Rend;
}

Sdio_State Sdio::CheckCmdResp3()
{
    while (!(STA & Sdio_Cmd_Rend))
    {
        if (STA & Sdio_Cmd_Out)
        {
            ICR = Sdio_Cmd_Out;
            return Sdio_Cmd_Out;
        }
        if (STA & Sdio_Cmd_Fail)
        {
            ICR = Sdio_Cmd_Fail;
            return Sdio_Cmd_Fail;
        }
    }
    ICR = Sdio_Cmd_Rend;
    return Sdio_Cmd_Rend;
}

Sdio_State Sdio::CheckCmdResp2()
{
    while (!(STA & Sdio_Cmd_Rend))
    {
        if (STA & Sdio_Cmd_Out)
        {
            ICR = Sdio_Cmd_Out;
            return Sdio_Cmd_Out;
        }
        if (STA & Sdio_Cmd_Fail)
        {
            ICR = Sdio_Cmd_Fail;
            return Sdio_Cmd_Fail;
        }
    }
    ICR = Sdio_Cmd_Rend;
    return Sdio_Cmd_Rend;
}

Sdio_State Sdio::CheckCmdResp6()
{
    while (!(STA & Sdio_Cmd_Rend))
    {
        if (STA & Sdio_Cmd_Out)
        {
            ICR = Sdio_Cmd_Out;
            return Sdio_Cmd_Out;
        }
        if (STA & Sdio_Cmd_Fail)
        {
            ICR = Sdio_Cmd_Fail;
            return Sdio_Cmd_Fail;
        }
    }
    ICR = Sdio_Cmd_Rend;
    return Sdio_Cmd_Rend;
}

Sdio_State Sdio::Command(u8 cmd, u32 arg, Sdio_Res_Type resp)
{
    ARG = arg;
    CMD = cmd | resp | (0b1 << 10);

    while (1)
    {
        if (STA & Sdio_Cmd_Sent)
        {
            ICR = Sdio_Cmd_Sent;
            return Sdio_Cmd_Sent;
        }
        if (STA & Sdio_Cmd_Rend)
        {
            ICR = Sdio_Cmd_Rend;
            return Sdio_Cmd_Rend;
        }

        if (STA & Sdio_Cmd_Out)
        {
            ICR = Sdio_Cmd_Out;
            return Sdio_Cmd_Out;
        }
        if (STA & Sdio_Cmd_Fail)
        {
            ICR = Sdio_Cmd_Fail;
            return Sdio_Cmd_Fail;
        }
    }
}

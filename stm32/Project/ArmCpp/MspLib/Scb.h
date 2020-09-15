//
// Created by Nc2016 on 2019/1/12.
//

#ifndef __SCB_H
#define __SCB_H

#include "Descriptor.h"


class Scb
{
public:
    __I  u32 CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
    __IO u32 ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
    __IO u32 VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
    __IO u32 AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    __IO u32 SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
    __IO u32 CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
    __IO u8  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    __IO u32 SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
    __IO u32 CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
    __IO u32 HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
    __IO u32 DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
    __IO u32 MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
    __IO u32 BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
    __IO u32 AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
    __I  u32 PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
    __I  u32 DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
    __I  u32 ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
    __I  u32 MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
    __I  u32 ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
    u32 RESERVED0[5U];
    __IO u32 CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */

};

#define SCB                 ((Scb *) 0xE000ED00U)


#endif //HELLO_SCB_H

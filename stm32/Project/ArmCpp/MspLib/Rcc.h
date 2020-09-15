//
// Created by Nc2016 on 2019/1/4.
//

#ifndef __RCC_H
#define __RCC_H

#include "Descriptor.h"
#include "Cortex.h"


#define Hse_Osc_Freq        25000000U
#define Hsi_Osc_Freq        16000000U

enum Pll_Src
{
    Pll_Src_Hsi = 0,
    Pll_Src_Hse = 1,
};

enum Clk_Src
{
    Clk_Src_Hsi = 0,
    Clk_Src_Hse = 1,
    Clk_Src_Pll = 2,
};

enum APB_Clk_Div
{
    APB_Clk_Div1 = 0x0u,
    APB_Clk_Div2 = 0x4u,
    APB_Clk_Div4 = 0x5u,
    APB_Clk_Div8 = 0x6u,
    APB_Clk_Div16 = 0x7u,
};

enum AHB_Clk_Div
{
    AHB_Clk_Div1 = 0x0000u,
    AHB_Clk_Div2 = 0x1000u,
    AHB_Clk_Div4 = 0x1001u,
    AHB_Clk_Div8 = 0x1010u,
    AHB_Clk_Div16 = 0x1011u,
    AHB_Clk_Div64 = 0x1100u,
    AHB_Clk_Div128 = 0x1101u,
    AHB_Clk_Div256 = 0x1110u,
    AHB_Clk_Div512 = 0x1111u,
};

enum AHB1_Dev
{
    AHB1_GpioA = 0x01u << 0,
    AHB1_GpioB = 0x01u << 1,
    AHB1_GpioC = 0x01u << 2,
    AHB1_GpioD = 0x01u << 3,
    AHB1_GpioE = 0x01u << 4,
    AHB1_GpioF = 0x01u << 5,
    AHB1_GpioG = 0x01u << 6,
    AHB1_GpioH = 0x01u << 7,
    AHB1_GpioI = 0x01u << 8,
    AHB1_DMA1 = 0x01u << 21,
    AHB1_DMA2 = 0x01u << 22,
};

enum APB1_Dev
{
    APB1_Tim2 = 0x01u << 0,
    APB1_Tim3 = 0x01u << 1,
    APB1_Tim4 = 0x01u << 2,
    APB1_Tim5 = 0x01u << 3,
    APB1_Tim6 = 0x01u << 4,
    APB1_Tim7 = 0x01u << 5,
    APB1_Tim12 = 0x01u << 6,
    APB1_Tim13 = 0x01u << 7,
    APB1_Tim14 = 0x01u << 8,
    APB1_Usart2 = 0x01u << 17,
    APB1_Power = 0x01u << 28,
};

enum APB2_Dev
{
    APB2_Usart1 = 0x01u << 4,
    APB2_Adc1 = 0x01u << 8,
    APB2_Adc2 = 0x01u << 9,
    APB2_Adc3 = 0x01u << 10,
    APB2_Sdio = 0x01u << 11,
};


class Rcc
{
public:
    __IO u32 CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
    __IO u32 PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
    __IO u32 CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
    __IO u32 CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
    __IO u32 AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
    __IO u32 AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
    __IO u32 AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
    u32 RESERVED0;     /*!< Reserved, 0x1C                                                                    */
    __IO u32 APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
    __IO u32 APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
    u32 RESERVED1;     /*!< Reserved, 0x28-0x2C                                                               */
    u32 RESERVED2;     /*!< Reserved, 0x28-0x2C                                                               */
    __IO u32 AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
    __IO u32 AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
    __IO u32 AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
    u32 RESERVED3;     /*!< Reserved, 0x3C                                                                    */
    __IO u32 APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
    __IO u32 APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
    u32 RESERVED4;     /*!< Reserved, 0x48-0x4C                                                               */
    u32 RESERVED5;     /*!< Reserved, 0x48-0x4C                                                               */
    __IO u32 AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
    __IO u32 AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
    __IO u32 AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
    u32 RESERVED6;     /*!< Reserved, 0x5C                                                                    */
    __IO u32 APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
    __IO u32 APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
    u32 RESERVED7;     /*!< Reserved, 0x68-0x6C                                                               */
    u32 RESERVED8;     /*!< Reserved, 0x68-0x6C                                                               */
    __IO u32 BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
    __IO u32 CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
    u32 RESERVED9;     /*!< Reserved, 0x78-0x7C                                                               */
    u32 RESERVED10;    /*!< Reserved, 0x78-0x7C                                                               */
    __IO u32 SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
    __IO u32 PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */

public:
    void SetDefault(void);

    void HseOn(void);

    void PllOn(void);

    void APB1Enable(APB1_Dev dev);

    void APB2Enable(APB2_Dev dev);

    void Pll(u32 M, u32 N, u32 P, u32 Q, Pll_Src src = Pll_Src_Hse);

    void Clk(AHB_Clk_Div H, APB_Clk_Div P1, APB_Clk_Div P2, Clk_Src src);

    void AHB1Enable(AHB1_Dev dev);
};

#define RCC                   ((Rcc *) 0x40023800U) //Page 65

#endif //HELLO_RCC_H

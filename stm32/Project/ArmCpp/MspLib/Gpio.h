//
// Created by Nc2016 on 2019/1/4.
//

#ifndef __GPIO_H
#define __GPIO_H

#include "Descriptor.h"

enum PIN
{
    Pin0 =1u<<0 ,
    Pin1 =1u<<1 ,
    Pin2 =1u<<2 ,
    Pin3 =1u<<3 ,
    Pin4 =1u<<4 ,
    Pin5 =1u<<5 ,
    Pin6 =1u<<6 ,
    Pin7 =1u<<7 ,
    Pin8 =1u<<8 ,
    Pin9 =1u<<9 ,
    Pin10=1u<<10,
    Pin11=1u<<11,
    Pin12=1u<<12,
    Pin13=1u<<13,
    Pin14=1u<<14,
    Pin15=1u<<15,
};

enum SPD
{
    Speed_Low=0u,
    Speed_Medium=1u,
    Speed_High=2u,
    Speed_Very_High=3u,
};


enum PULL
{
    No_Pull=0,
    Pull_Up=1,
    Pull_Down=2,
};

enum AFIO
{
    AF0_System             =0u,
    AF1_Tim1_2             =1u,
    AF2_Tim3_5             =2u,
    AF3_Tim8_11            =3u,
    AF4_Iic1_3             =4u,
    AF5_Spi1_2             =5u,
    AF6_Spi3               =6u,
    AF7_Usart1_3           =7u,
    AF8_Usart4_6           =8u,
    AF9_Can1_2_Tim12_14    =9u,
    AF10_OtgFs_Otg_Hs      =10u,
    AF11_Eth               =11u,
    AF12_Fsmc_Sdio_OtgHs   =12u,
    AF13_Dcmi              =13u,
    AF14_Ltdc              =14u,
    AF15_EventOut          =15u,
};


class Gpio
{
public:
    __IO u32 MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
    __IO u32 OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
    __IO u32 OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
    __IO u32 PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    __IO u32 IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
    __IO u32 ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
    __IO u32 BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
    __IO u32 LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    __IO u32 AFRL  ;   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
    __IO u32 AFRH  ;   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */

    void OutPp(u32 pin);

    void OutOd(u32 pin);

    void Down(u32 b);

    void Up(u32 b);

    void AfPp(u32 pin);

    void Speed(u32 pin, SPD speed);

    void Pull(u32 pin, PULL pull);

    void Alternate(u32 pin, AFIO af);

    void Anal(u32 pin);

    void In(u32 pin);
};

#define GPIOA                 ((Gpio *) 0x40020000U)
#define GPIOB                 ((Gpio *) 0x40020400U)
#define GPIOC                 ((Gpio *) 0x40020800U)
#define GPIOD                 ((Gpio *) 0x40020C00U)
#define GPIOE                 ((Gpio *) 0x40021000U)
#define GPIOF                 ((Gpio *) 0x40021400U)
#define GPIOG                 ((Gpio *) 0x40021800U)
#define GPIOH                 ((Gpio *) 0x40021C00U)
#define GPIOI                 ((Gpio *) 0x40022000U)


#endif //HELLO_GPIO_H

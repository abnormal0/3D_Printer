//
// Created by draw on 19-4-17.
//

#ifndef _TIM_H
#define _TIM_H

#include "Descriptor.h"



class Tim
{
public:
    __IO u32 CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
    __IO u32 CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
    __IO u32 SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
    __IO u32 DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    __IO u32 SR;          /*!< TIM status register,                 Address offset: 0x10 */
    __IO u32 EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
    __IO u32 CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
    __IO u32 CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
    __IO u32 CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
    __IO u32 CNT;         /*!< TIM counter register,                Address offset: 0x24 */
    __IO u32 PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
    __IO u32 ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
    __IO u32 RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
    __IO u32 CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
    __IO u32 CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
    __IO u32 CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
    __IO u32 CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
    __IO u32 BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
    __IO u32 DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
    __IO u32 DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
    __IO u32 OR;          /*!< TIM option register,                 Address offset: 0x50 */
    void Sleep(u16 psc, u16 arr);
    void Run(u16 psc, u16 arr);
    void Pwm1(u16 psc, u16 arr);
    void Pwm2(u16 psc, u16 arr);
    void Pwm3(u16 psc, u16 arr);
    void Pwm4(u16 psc, u16 arr);

    void Start(u32 psc);
};

#define TIM2                ((Tim *) 0x40000000U)
#define TIM3                ((Tim *) 0x40000400U)
#define TIM4                ((Tim *) 0x40000800U)
#define TIM5                ((Tim *) 0x40000C00U)
#define TIM6                ((Tim *) 0x40001000U)
#define TIM7                ((Tim *) 0x40001400U)
#define TIM12                ((Tim *) 0x40001800U)


#endif //ARMCPP_TIM_H

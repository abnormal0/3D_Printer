//
// Created by draw on 19-4-19.
//

#ifndef _ADC_H
#define _ADC_H

#include "Descriptor.h"

enum Adc_Smp
{
    Adc_Smp_3Clk=0,
    Adc_Smp_15Clk=1,
    Adc_Smp_28Clk=2,
    Adc_Smp_56Clk=3,
    Adc_Smp_84Clk=4,
    Adc_Smp_112Clk=5,
    Adc_Smp_144Clk=6,
    Adc_Smp_480Clk=7,
};

enum Adc_Trigger
{
    Trigger_Timer1_CH1 = 0b0000 << 24,
    Trigger_Timer1_CH2 = 0b0001 << 24,
    Trigger_Timer1_CH3 = 0b0010 << 24,
    Trigger_Timer2_CH2 = 0b0011 << 24,
    Trigger_Timer2_CH3 = 0b0100 << 24,
    Trigger_Timer2_CH4 = 0b0101 << 24,
    Trigger_Timer2_TRGO = 0b0110 << 24,
    Trigger_Timer3_CH1 = 0b0111 << 24,
    Trigger_Timer3_TRGO = 0b1000 << 24,
    Trigger_Timer4_CH4 = 0b1001 << 24,
    Trigger_Timer5_CH1 = 0b1010 << 24,
    Trigger_Timer5_CH2 = 0b1011 << 24,
    Trigger_Timer5_CH3 = 0b1100 << 24,
    Trigger_Timer8_CH1 = 0b1101 << 24,
    Trigger_Timer8_TRGO = 0b1110 << 24,
    Trigger_Exit_Line11 = 0b1110 << 24,
};

class Adc
{
public:
    __IO u32 SR;     /*!< ADC status register,                         Address offset: 0x00 */
    __IO u32 CR1;    /*!< ADC control register 1,                      Address offset: 0x04 */
    __IO u32 CR2;    /*!< ADC control register 2,                      Address offset: 0x08 */
    __IO u32 SMPR1;  /*!< ADC sample time register 1,                  Address offset: 0x0C */
    __IO u32 SMPR2;  /*!< ADC sample time register 2,                  Address offset: 0x10 */
    __IO u32 JOFR1;  /*!< ADC injected channel data offset register 1, Address offset: 0x14 */
    __IO u32 JOFR2;  /*!< ADC injected channel data offset register 2, Address offset: 0x18 */
    __IO u32 JOFR3;  /*!< ADC injected channel data offset register 3, Address offset: 0x1C */
    __IO u32 JOFR4;  /*!< ADC injected channel data offset register 4, Address offset: 0x20 */
    __IO u32 HTR;    /*!< ADC watchdog higher threshold register,      Address offset: 0x24 */
    __IO u32 LTR;    /*!< ADC watchdog lower threshold register,       Address offset: 0x28 */
    __IO u32 SQR1;   /*!< ADC regular sequence register 1,             Address offset: 0x2C */
    __IO u32 SQR2;   /*!< ADC regular sequence register 2,             Address offset: 0x30 */
    __IO u32 SQR3;   /*!< ADC regular sequence register 3,             Address offset: 0x34 */
    __IO u32 JSQR;   /*!< ADC injected sequence register,              Address offset: 0x38*/
    __IO u32 JDR1;   /*!< ADC injected data register 1,                Address offset: 0x3C */
    __IO u32 JDR2;   /*!< ADC injected data register 2,                Address offset: 0x40 */
    __IO u32 JDR3;   /*!< ADC injected data register 3,                Address offset: 0x44 */
    __IO u32 JDR4;   /*!< ADC injected data register 4,                Address offset: 0x48 */
    __IO u32 DR;     /*!< ADC regular data register,                   Address offset: 0x4C */

    void Group(u32 n);

    void Ch(u32 od, u32 ch);

    void Start(void);

    void Mode(bl scan, bl cont);

    void Iqr(bl en);

    void EocEach(bl eoc);

    void Dma(bl d);

    void On(void);

    void ExtTri(bl ri, bl fa);

    void TriEven(Adc_Trigger trigger);

    u16 GetValue(u32 ch);

    void Sample(u32 ch, Adc_Smp smp);
};

class AdcCommon
{

};

#define ADC1                 ((Adc *) 0x40012000U)
#define ADC2                 ((Adc *) 0x40012100U)
#define ADC3                 ((Adc *) 0x40012200U)
#define ADCM                 ((AdcCommon *) 0x40012300U)

#endif //ARMCPP_ADC_H

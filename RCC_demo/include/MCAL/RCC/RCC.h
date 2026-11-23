#ifndef RCC_H
#define RCC_H
#include <stdint.h>
#include "RCC_Priv.h"

typedef enum
{

    RCC_OK,
    RCC_Timeout,
    RCC_NULLptr,
    RCC_Invalidparam,
    RCC_CLKNotready,
    RCC_clkInUse
  
} RCC_errcode;

typedef enum
{
    HSI,
    HSE,
    PLL
} RCC_Clk;

typedef enum
{
    CLK_Ready,
    CLK_Not_ready
} RCC_Ready_status;

typedef enum
{
    CLK_ON,
    CLK_OFF
} RCC_enuClkStatus;


typedef struct
{
    uint32_t  PLL_u32M;
    uint32_t PLL_u32N;
    
    uint32_t PLL_u32P;
    uint32_t PLL_u32Q;
    RCC_Clk PLL_clksrc;
} RCC_strPll;

typedef enum
{
    AHB1,
    AHB2,
    APB1,
    APB2
} RCC_buses;

typedef enum{

     APB_notDiv=3,
    APB_div2,
    APB_div4,
    APB_div8,
    APB_div16,
    notDiv=7,
    div2,
    div4,
    div8,
    div16,
    div64,
    div128,
    div256,
    div512

}RCC_busPrescaler;



typedef enum
{
    
    //AHB1
    GPIOAEN=0,
    GPIOBEN,
    GPIOCEN,
    GPIODEN,
    GPIOEEN,
    GPIOHEN=7,
    CRCEN=12,
    DMA1EN=21,
    DMA2EN=22,
  

    //AHB2
    OTGFSEN=0,
    //APB1
    TIM2EN=0,
    TIM3EN,
    TIM4EN,
    TIM5EN,
    WWDGEN=11,
    SPI2EN=14,
    SPI3EN=15,
    USART2EN=17,
    I2C1EN=21,
    I2C2EN,
    I2C3EN,
    PWREN=28,

    //APB2
    TIM1EN,
    USART1EN=4,
    USART6EN,
    ADC1EN=8,
    SDIOEN=11,
    SPI1EN,
    SPI4EN,
    SYSCFGEN,
    TIM9EN=16,
    TIM10EN,
    TIM11EN

} RCC_periph;


typedef enum
{   
    RMVF =24,
    BORRSTF,
    PINRSTF,
    PORRSTF,
    SFTRSTF,
    IWDGRSTF,
    WWDGRSTF,
    LPWRRSTF
    
} RCC_Resetcause;

RCC_errcode RCC_enuSlktSysClk(RCC_Clk clk);
RCC_errcode RCC_enuClkCtrl(RCC_Clk clk, RCC_enuClkStatus status);
RCC_errcode RCC_enuPLL_CNFG(volatile RCC_strPll *ref_str);
RCC_errcode RCC_enuSetPrescaler(RCC_buses bus, RCC_busPrescaler pres);
RCC_errcode RCC_enuPeripheralCLK(RCC_periph prph, RCC_enuClkStatus stat, RCC_buses bus);
RCC_errcode RCC_enuGetSysCLKFreq(uint32_t *f); //
RCC_errcode RCC_enuGetResetCause(RCC_Resetcause *r);
RCC_errcode RCC_enuGetCLKstat(RCC_Ready_status *r);
RCC_errcode RCC_enuGetSysCLK(RCC_Clk *c);

#endif
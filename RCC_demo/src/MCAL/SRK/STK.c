#include "./MCAL/STK/STK_PRIV.h"
#include "./MCAL/STK/STK.h"
#include "./MCAL/RCC/RCC.h"

#include <stdint.h>

// static function to save the call back function in it
static func_ptr_t STk_callback = NULL;
static volatile uint64_t Timems = 0;      // the real ticks that the systic already do
static volatile uint32_t requestTime = 0; // the time that i want to do some thing on it
STK_enuErrorCode STK_enuDelayMs(uint32_t del)
{

    // uint32_t N = 0; // 15999because the hsi has 16 MHZ , we can chane the sourse then the function will be make 1 ms in one load in the freq value -1
    // RCC_Clk C = HSI;
    // RCC_enuGetSysCLK(&C);
    // if (C == HSI)
    //     N = 15999;
    // if (C == HSE)
    //     N = 24999;
    // if (C == PLL)
    //     N = 83999;

    // STK->CTRL &= ~(1UL << ENABLE); // 1/1000              //hsi/1000
    // STK->CTRL |= (1UL << CLKSOURCE);

    // STK->VAL = (1UL << CURRENT); // make sure to make the countflag and the reload val is 0 in the first because the reload value has undefine behavoir on reset
    // STK->LOAD = N;
    // STK->CTRL |= (1UL << ENABLE);
    // while (del)
    // {

    //     while (!(STK->CTRL & (1UL << COUNTFLAG)))
    //         ;

    //     del--;
    // }
    return STK_OK;
}

STK_enuErrorCode STK_enuSYSInit()
{

    STK->CTRL &= ~(1UL << ENABLE); // to make sure that the cfg will be ok should make it 0 in the first
    STK->CTRL |= (1UL << TICKINT); // to enable the inturrub or assert the systick exeption request
    STK->CTRL |= (1UL << CLKSOURCE); // to enable the inturrub or assert the systick exeption request
    // STK->VAL = (1UL << CURRENT);   // to reset the currant reload val
    RCC_Clk C = HSI;
    RCC_enuGetSysCLK(&C);
    uint32_t N = 0U;
    if (C == HSI)
        N = 15999;
    if (C == HSE)
        N = 24999;
    if (C == PLL)
        N = 83999;
    STK->LOAD = N; // if i work on hsi
    return STK_OK;
}

STK_enuErrorCode STK_enuStart()
{

    // STK->VAL = (1UL << CURRENT);
    STK->CTRL |= (1UL << ENABLE);
    return STK_OK;
}

STK_enuErrorCode STK_enuStop()
{
    STK->CTRL &= ~(1UL << ENABLE);
    return STK_OK;
}

STK_enuErrorCode STK_enuSetCBF(func_ptr_t func)
{

    if (func == NULL)
        return STK_NULLPTR;

    STk_callback = func;

    return STK_OK;
}

STK_enuErrorCode STK_enuNotifyms(uint64_t time)
{
    if (time <= 0)
        return STK_INVALIDPARAM;

    requestTime = time;
    return STK_OK;
}
STK_enuErrorCode STK_enuGetTick(uint64_t *tick)
{
    if (tick == NULL)
        return STK_NULLPTR;

    *tick = Timems;

    return STK_OK;
}
void SysTick_Handler(void)
{

    Timems++;

    if(Timems %requestTime==0)
     {
        if(STk_callback!=NULL) STk_callback();
     }

    //    return STK_OK;
}
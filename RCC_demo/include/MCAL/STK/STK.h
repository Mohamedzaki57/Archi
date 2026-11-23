#ifndef STK_H
#define STK_H
#include <stdio.h>
#include <stdint.h>

typedef void(*func_ptr_t) (void);

typedef enum{
    STK_OK,
    STK_INVALIDPARAM,
    STK_NULLPTR
}STK_enuErrorCode;

STK_enuErrorCode STK_enuDelayMs(uint32_t del);
STK_enuErrorCode STK_enuSYSInit();
STK_enuErrorCode STK_enuStart();
STK_enuErrorCode STK_enuStop();
STK_enuErrorCode STK_enuSetCBF(func_ptr_t );
STK_enuErrorCode STK_enuNotifyms(uint64_t);

STK_enuErrorCode STK_enuGetTick(uint64_t *tick);


#endif
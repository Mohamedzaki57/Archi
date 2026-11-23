#ifndef SCHED_H
#define SCHED_H
#include<stdint.h>
#include"./MCAL/STK/STK.h"
#include "./MCAL/NVIC/NVIC.h"


#define maxrunns 100


typedef struct{
    func_ptr_t callback;
    uint32_t cycle_time;
    uint32_t firstDelay;
    uint32_t lastTime;
    uint32_t priority;
    

}SCHED_strRunnables;

typedef enum{
    SCHED_OK,
    SCHED_FAILED,
    SCHED_NULLPTR,
    SCHED_INVALIDPARAM,
    SCHED_RUNNING,
    SCHED_STOP,
    SCHED_FULLRUNS
}SCHED_enuErrorCode;

SCHED_enuErrorCode SCHED_init();
SCHED_enuErrorCode SCHED_Start();
SCHED_enuErrorCode SCHED_Stop();
SCHED_enuErrorCode SCHED_registerRunnable(const SCHED_strRunnables*);
SCHED_enuErrorCode SCHED_removeRunnable(SCHED_strRunnables*);






#endif
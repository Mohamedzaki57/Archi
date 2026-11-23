
#include "./APP/SCHED/SCHED.h"
#define base 0
#define mxprio 32
volatile static uint8_t isTregger = 0;
volatile static  uint64_t TimeMS = 0;
static volatile uint32_t curRunns = 0;
static SCHED_strRunnables SCHED_stcRunnables[maxrunns];

static void SCHED_handler(void);

SCHED_enuErrorCode SCHED_init()
{
    if (STK_enuSYSInit() != STK_OK)
        return SCHED_FAILED;
    if (STK_enuSetCBF(SCHED_handler) != STK_OK)
        return SCHED_FAILED;
    if (STK_enuNotifyms(1) != STK_OK)
        return SCHED_FAILED;
    return SCHED_OK;
}
SCHED_enuErrorCode SCHED_Start()
{

    // if (curRunns == 0)
    //     return SCHED_FAILED;
    STK_enuStart();

    while (1)
    {
        if (isTregger)
        {
            isTregger=0;
            // STK_enuGetTick(TimeMS);
            TimeMS++;
            for (int i = 0; i < maxrunns; i++)
            {
                if (SCHED_stcRunnables[i].callback != NULL)
                {

                    if ((TimeMS >= SCHED_stcRunnables[i].firstDelay) && (((TimeMS- SCHED_stcRunnables[i].firstDelay) % (SCHED_stcRunnables[i].cycle_time)  == 0)))
                    {
                        SCHED_stcRunnables[i].callback();
                    }
                }
            }
        }
    }

    return SCHED_OK;
}

SCHED_enuErrorCode SCHED_Stop()
{
    STK_enuStop();
    return SCHED_OK;
}

SCHED_enuErrorCode SCHED_registerRunnable(const SCHED_strRunnables *curreg)
{

    if (curreg == NULL)
        return SCHED_FAILED;
    if (curRunns >= maxrunns)
        return SCHED_FULLRUNS;

    if (curreg->callback == NULL)
    {
        return SCHED_INVALIDPARAM;
    }
    if (curreg->cycle_time == base)
    {
        return SCHED_INVALIDPARAM;
    }
    if (curreg->firstDelay < base)
    {
        return SCHED_INVALIDPARAM;
    }
    if (curreg->lastTime < base)
    {
        return SCHED_INVALIDPARAM;
    }
    if (curreg->priority > mxprio)
    {
        return SCHED_INVALIDPARAM;
    }

    SCHED_stcRunnables[curreg->priority].callback = curreg->callback;

    SCHED_stcRunnables[curreg->priority].cycle_time = curreg->cycle_time;

    SCHED_stcRunnables[curreg->priority].firstDelay = curreg->firstDelay;

    SCHED_stcRunnables[curreg->priority].lastTime = curreg->lastTime;

    SCHED_stcRunnables[curreg->priority].priority = curreg->priority;

    // curRunns++;
    return SCHED_OK;
}

static void SCHED_handler(void)
{
    isTregger = 1;
}

SCHED_enuErrorCode SCHED_removeRunnable(SCHED_strRunnables *curremove)
{

    return SCHED_OK;
}


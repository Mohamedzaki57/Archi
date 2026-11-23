
#include "./MCAL/NVIC/NVIC.h"
#include "./MCAL/NVIC/NVIC_PRIV.h"

NVIC_enuErrCode NVIC_EnableIRQ(NVIC_IQR_enu IRQn)
{
    if (IRQn < WWDG_IRQn || IRQn > SPI4_IRQn)
        return NVIC_INVALPARAM;

    NVIC->NVIC_ISER[IRQn / NVIC_mod] |= (1 << IRQn % NVIC_mod);
    return NVIC_OK;
}

NVIC_enuErrCode NVIC_DisableIRQ(NVIC_IQR_enu IRQn)
{

    if (IRQn < WWDG_IRQn || IRQn > SPI4_IRQn)
        return NVIC_INVALPARAM;

    NVIC->NVIC_ICER[IRQn / NVIC_mod] |= (1 << IRQn % NVIC_mod);
    return NVIC_OK;
}
NVIC_enuErrCode NVIC_SetPendingIRQ(NVIC_IQR_enu IRQn)
{
    if (IRQn < WWDG_IRQn || IRQn > SPI4_IRQn)
        return NVIC_INVALPARAM;

    NVIC->NVIC_ISPR[IRQn / NVIC_mod] |= (1 << IRQn % NVIC_mod);
    return NVIC_OK;
}

NVIC_enuErrCode NVIC_ClearPendingIRQ(NVIC_IQR_enu IRQn)
{
    if (IRQn < WWDG_IRQn || IRQn > SPI4_IRQn)
        return NVIC_INVALPARAM;

    NVIC->NVIC_ICPR[IRQn / NVIC_mod] |= (1 << IRQn % NVIC_mod);
    return NVIC_OK;
}

NVIC_enuErrCode NVIC_GetPendingIRQ(NVIC_IQR_enu IRQn, uint32_t *pend)
{

    if (IRQn < WWDG_IRQn || IRQn > SPI4_IRQn)
        return NVIC_INVALPARAM;

    *pend = (NVIC->NVIC_ISPR[IRQn / NVIC_mod] & (1 << IRQn % NVIC_mod));

    return NVIC_OK;
}

NVIC_enuErrCode NVIC_SetPriority(NVIC_IQR_enu IRQn, uint8_t priority)
{

    if (IRQn < WWDG_IRQn || IRQn > SPI4_IRQn)
        return NVIC_INVALPARAM;
    if (priority < NVIC_start || priority > NVIC_end)
        return NVIC_INVALPARAM;

    NVIC->NVIC_IPR[IRQn] = priority;
    return NVIC_OK;
}

NVIC_enuErrCode NVIC_GetPriority(NVIC_IQR_enu IRQn, uint8_t *priority)
{

    if (IRQn < WWDG_IRQn || IRQn < SPI4_IRQn)
        return NVIC_INVALPARAM;

   *priority=NVIC->NVIC_IPR[IRQn];

   return NVIC_OK;
    
}
